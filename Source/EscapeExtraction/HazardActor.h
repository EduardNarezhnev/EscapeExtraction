// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazardConfig.h"
#include "HazardActor.generated.h"

UCLASS()
class ESCAPEEXTRACTION_API AHazardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazardActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	UHazardConfig* Config;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	UMaterialInterface* ActiveMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	UMaterialInterface* InactiveMaterial;

	UPROPERTY(BlueprintReadOnly, Category = "Hazard")
	bool bIsActive = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	void MoveTowardsPlayer(float DeltaTime);
	void ReturnToBase(float DeltaTime);
	void ApplyDamageToPlayer(AActor* Player);
	void ResetDamageCooldown();
	void UpdateVisualState();

private:
	FVector InitialLocation;

	// Cached player pointer (optimization)
	class AEscapeExtractionCharacter* CachedPlayer = nullptr;

	bool bCanApplyDamage = true;
	FTimerHandle DamageCooldownTimer;

	void UpdateHazardState(float Distance);


};
