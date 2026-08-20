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
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEscapeExtractionCharacter::AEscapeExtractionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	CameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void AEscapeExtractionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(HealthComponent)
	{
		PreviousHealth = HealthComponent->CurrentHealth;;
		HealthComponent->OnHealthDepleted.AddDynamic(this, &AEscapeExtractionCharacter::HandleDeath);
		HealthComponent->OnHealthChanged.AddDynamic(this, &AEscapeExtractionCharacter::OnHealthChanged);
	}
}

void AEscapeExtractionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetVelocity().Size() > 0.0f && GetCharacterMovement()->IsMovingOnGround())
	{
		FootstepTimer -= DeltaTime;
		if(FootstepTimer <= 0.0f)
		{
			PlayFootstep();
			FootstepTimer = FootstepInterval;
		}
	}
	else
	{
		FootstepTimer = 0.0f;
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
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEscapeExtractionCharacter::StopJump);
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
	APlayerController* PC = Cast<APlayerController>(GetController());
	if(PC)
	{
		if(CurrentHealth < PreviousHealth)
		{
			BP_ShowDamageEffect();	
			if(DamageSound)
			{
				UGameplayStatics::PlaySound2D(this, DamageSound);
			}
		}
		else if(CurrentHealth > PreviousHealth)
		{
			BP_ShowHealEffect();
			if(HealSound)
			{
				UGameplayStatics::PlaySound2D(this, HealSound);
			}
		}
		
		PreviousHealth = CurrentHealth;
	}	
}

void AEscapeExtractionCharacter::PlayFootstep()
{
	if(FootstepSounds.Num() == 0) return;

	int32 RandomIndex = FMath::RandRange(0, FootstepSounds.Num() - 1);
	USoundBase* SelectedSound = FootstepSounds[RandomIndex];

	if(SelectedSound)
	{
		UGameplayStatics::PlaySound2D(this, SelectedSound);
	}
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
		// Enabling input after restart (unreal forgets to do so)
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

