// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HazardConfig.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ESCAPEEXTRACTION_API UHazardConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	float DamageAmount = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	float ActivationDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	float DeactivationDistance = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	float MoveSpeed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	float DamageCooldown = 1.0f;
};
