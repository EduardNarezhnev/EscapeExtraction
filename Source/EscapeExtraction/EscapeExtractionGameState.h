// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EscapeExtractionGameState.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEEXTRACTION_API AEscapeExtractionGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game")
	int32 CollectedItemsCount = 0;
	
};
