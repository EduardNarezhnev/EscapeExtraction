// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeExtractionGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EscapeExtractionGameState.h"
#include "EscapeExtractionPlayerController.h"

AEscapeExtractionGameMode::AEscapeExtractionGameMode()
{
    PlayerControllerClass = AEscapeExtractionPlayerController::StaticClass();
    GameStateClass = AEscapeExtractionGameState::StaticClass();
}

void AEscapeExtractionGameMode::BeginPlay()
{
    Super::BeginPlay();

    CurrentState = EGameState::InProgress;
}

void AEscapeExtractionGameMode::GameOver(bool bWon)
{
    if(CurrentState == EGameState::GameOver)
    {
        return;
    }

    CurrentState = EGameState::GameOver;

    UWorld* World = GetWorld();
    if(World)
    {
        APlayerController* PC = World->GetFirstPlayerController();
        if(PC)
        {
            PC->SetPause(true);
            PC->SetInputMode(FInputModeUIOnly());
            PC->bShowMouseCursor = true;
        }
    }

    BP_GameOver(bWon);
}

void AEscapeExtractionGameMode::RestartGame()
{
    if(CurrentState != EGameState::GameOver)
    {
        return;
    }

    PerformRestart();
}

void AEscapeExtractionGameMode::PerformRestart()
{
    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}

