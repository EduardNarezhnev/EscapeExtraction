// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "KeyPickup.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEEXTRACTION_API AKeyPickup : public APickupActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup");
	int32 KeyCount = 1;

protected:
	virtual void ApplyEffect(AEscapeExtractionCharacter* Character) override;
	
};
