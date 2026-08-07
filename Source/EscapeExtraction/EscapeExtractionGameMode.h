// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EscapeExtractionGameMode.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	WaitingToStart UMETA(DisplayName = "Waiting to Start"),
	InProgress UMETA(DisplayName = "In Progress"),
	GameOver UMETA(DisplayName = "Game Over")
};

UCLASS()
class ESCAPEEXTRACTION_API AEscapeExtractionGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEscapeExtractionGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Settings")
	int32 ItemsToCollect = 3;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver(bool bWon);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	EGameState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetCurrentState(EGameState NewState) { CurrentState = NewState; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Game")
	void BP_GameOver(bool bWon);

protected:
	virtual void BeginPlay() override;

private:
	EGameState CurrentState = EGameState::WaitingToStart;

	FTimerHandle RestartTimerHandle;

	void PerformRestart();
};
