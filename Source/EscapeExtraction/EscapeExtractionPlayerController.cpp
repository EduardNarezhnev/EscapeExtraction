// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeExtractionPlayerController.h"
#include "EscapeExtractionGameMode.h"

void AEscapeExtractionPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(HUDClass)
    {
        HUDWidget = CreateWidget<UUserWidget>(this, HUDClass);
        if(HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void AEscapeExtractionPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("Pause", IE_Pressed, this, &AEscapeExtractionPlayerController::TogglePause);
}

void AEscapeExtractionPlayerController::TogglePause()
{
    AEscapeExtractionGameMode* GM = GetWorld()->GetAuthGameMode<AEscapeExtractionGameMode>();
    if(!GM) return;

    if(GM->GetCurrentState() != EGameState::InProgress) return;

    bIsPaused = !bIsPaused;
    SetPause(bIsPaused);

    if(bIsPaused)
    {
        if(PauseMenuClass)
        {
            PauseWidget = CreateWidget<UUserWidget>(this, PauseMenuClass);
            if(PauseWidget)
            {
                PauseWidget->AddToViewport();
                SetInputMode(FInputModeUIOnly());
                bShowMouseCursor = true;
            }
        }
    }
    else
    {
        if(PauseWidget)
        {
            PauseWidget->RemoveFromParent();
            PauseWidget = nullptr;
            SetInputMode(FInputModeGameOnly());
            bShowMouseCursor = false;
        }
    }
}
