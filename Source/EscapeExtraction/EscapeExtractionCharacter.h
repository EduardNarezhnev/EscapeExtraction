// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EscapeExtractionCharacter.generated.h"

UCLASS()
class ESCAPEEXTRACTION_API AEscapeExtractionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEscapeExtractionCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	class UHealthComponent* HealthComponent;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Inventory")
	int32 CollectedItems = 0;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	bool bIsDangerNear = false;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(int32 Count = 1);

	UFUNCTION()
	void HandleDeath();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void StartJump();
	void StopJump();

private:
	UFUNCTION()
	void OnHealthChanged(float CurrentHealth);
};
