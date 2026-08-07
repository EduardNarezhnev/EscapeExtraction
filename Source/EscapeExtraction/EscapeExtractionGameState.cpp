// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeExtractionGameState.h"
#include "Net/UnrealNetwork.h"

void AEscapeExtractionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AEscapeExtractionGameState, CollectedItemsCount);
}
