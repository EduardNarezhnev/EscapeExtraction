// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeExtractionCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "HealthComponent.h"
#include "EscapeExtractionGameMode.h"
#include "EscapeExtractionGameState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEscapeExtractionCharacter::AEscapeExtractionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void AEscapeExtractionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(HealthComponent)
	{
		HealthComponent->OnHealthDepleted.AddDynamic(this, &AEscapeExtractionCharacter::HandleDeath);
		HealthComponent->OnHealthChanged.AddDynamic(this, &AEscapeExtractionCharacter::OnHealthChanged);
	}
}

// Called to bind functionality to input
void AEscapeExtractionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeExtractionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeExtractionCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AEscapeExtractionCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AEscapeExtractionCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEscapeExtractionCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEscapeExtractionCharacter::StopJump);
}

void AEscapeExtractionCharacter::MoveForward(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AEscapeExtractionCharacter::MoveRight(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AEscapeExtractionCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AEscapeExtractionCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AEscapeExtractionCharacter::StartJump()
{
	Jump();
}

void AEscapeExtractionCharacter::StopJump()
{
	StopJumping();
}

void AEscapeExtractionCharacter::AddItem(int32 Count)
{
	CollectedItems += Count;

	AEscapeExtractionGameState* GS = GetWorld()->GetGameState<AEscapeExtractionGameState>();
	if(GS)
	{
		GS->CollectedItemsCount += Count;
	}
}

void AEscapeExtractionCharacter::HandleDeath()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if(PC)
	{
		PC->DisableInput(PC);
		PC->SetInputMode(FInputModeUIOnly());
		PC->bShowMouseCursor = true;
	}

	AEscapeExtractionGameMode* GM = GetWorld()->GetAuthGameMode<AEscapeExtractionGameMode>();
	if(GM)
	{
		GM->GameOver(false);
	}
}

void AEscapeExtractionCharacter::OnHealthChanged(float CurrentHealth)
{
	
}

void AEscapeExtractionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEscapeExtractionCharacter, CollectedItems);
}

void AEscapeExtractionCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
  
	if (APlayerController* PC = Cast<APlayerController>(NewController))
    {
        PC->EnableInput(PC);
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
    }
}

float AEscapeExtractionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (HealthComponent)
    {
        HealthComponent->TakeDamage(DamageAmount);
        return DamageAmount;
    }

    return 0.0f;
}

