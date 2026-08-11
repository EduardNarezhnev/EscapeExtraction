// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ExtractionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEEXTRACTION_API AExtractionTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AExtractionTrigger();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;
};
