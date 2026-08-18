// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EscapeExtractionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEEXTRACTION_API AEscapeExtractionPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void TogglePause();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* HUDWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* PauseWidget = nullptr;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void BP_ShowHUDMessage(const FString& Message, float Duration);
	
private:
	bool bIsPaused = false;

};
