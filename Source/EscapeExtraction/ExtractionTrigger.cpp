// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "EscapeExtractionCharacter.h"
#include "EscapeExtractionGameMode.h"
#include "EscapeExtractionGameState.h"
#include "Kismet/GameplayStatics.h"

AExtractionTrigger::AExtractionTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionProfileName("NoCollision");
}

void AExtractionTrigger::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &AExtractionTrigger::OnOverlapBegin);
}

void AExtractionTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    AEscapeExtractionCharacter* Player = Cast<AEscapeExtractionCharacter>(OtherActor);
    if(!Player) return;

    AEscapeExtractionGameMode* GM = GetWorld()->GetAuthGameMode<AEscapeExtractionGameMode>();
    if(!GM || GM->GetCurrentState() != EGameState::InProgress) return;

    AEscapeExtractionGameState* GS = GetWorld()->GetGameState<AEscapeExtractionGameState>();
    if(!GS) return;

    if(GS->CollectedItemsCount >= GM->ItemsToCollect)
    {
        GM->GameOver(true);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Red,
            FString::Printf(TEXT("Need %d more keys!"), GM->ItemsToCollect - GS->CollectedItemsCount)
        );
    }
}