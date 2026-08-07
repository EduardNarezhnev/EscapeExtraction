// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEEXTRACTION_API AHealthPickup : public APickupActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float HealAmount = 20.0f;

protected:
	virtual void ApplyEffect(AEscapeExtractionCharacter* Character) override;
};
