// Fill out your copyright notice in the Description page of Project Settings.


#include "HazardActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EscapeExtractionCharacter.h"
#include "EscapeExtractionGameMode.h"
#include "HazardConfig.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

// Sets default values
AHazardActor::AHazardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = MeshComponent;
    MeshComponent->SetCollisionProfileName("OverlapAllDynamic");

    BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollisionComponent->SetupAttachment(RootComponent);
    BoxCollisionComponent->SetCollisionProfileName("OverlapAllDynamic");
    BoxCollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
}

// Called when the game starts or when spawned
void AHazardActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();

	CachedPlayer = Cast<AEscapeExtractionCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHazardActor::OnOverlapBegin);

	if(InactiveMaterial)
	{
		MeshComponent->SetMaterial(0, InactiveMaterial);
	}
}

// Called every frame
void AHazardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AEscapeExtractionGameMode* GM = GetWorld()->GetAuthGameMode<AEscapeExtractionGameMode>();
	if(!GM || GM->GetCurrentState() != EGameState::InProgress)
	{
		if(bIsActive)
		{
			bIsActive = false;
			if(CachedPlayer)
			{
				CachedPlayer->bIsDangerNear = false;
			}
			UpdateVisualState();
		}

		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), InitialLocation, DeltaTime, 2.0f);
		SetActorLocation(NewLocation);
		return;
	}

	if(!CachedPlayer) return;

	float Distance = FVector::Dist(GetActorLocation(), CachedPlayer->GetActorLocation());

	UpdateHazardState(Distance);

	if (bIsActive && bCanApplyDamage && CachedPlayer)
    {
        if (BoxCollisionComponent->IsOverlappingActor(CachedPlayer))
        {
            ApplyDamageToPlayer(CachedPlayer);
        }
    }
}

void AHazardActor::UpdateHazardState(float Distance)
{
	float ActivationDist = Config ? Config->ActivationDistance : 500.0f;
	float DeactivationDist = Config ? Config->DeactivationDistance : 800.0f;

	if(Distance < ActivationDist)
	{
		if(!bIsActive)
		{
			bIsActive = true;
			if(CachedPlayer)
			{
				CachedPlayer->bIsDangerNear = true;
			}
			UpdateVisualState();
		}
		MoveTowardsPlayer(GetWorld()->GetDeltaSeconds());
	}
	else if(Distance > DeactivationDist)
	{
		if(bIsActive)
		{
			bIsActive = false;
			if(CachedPlayer)
			{
				CachedPlayer->bIsDangerNear = false;
			}
			UpdateVisualState();
		}
		ReturnToBase(GetWorld()->GetDeltaSeconds());
	}
	else if(bIsActive)
	{
		MoveTowardsPlayer(GetWorld()->GetDeltaSeconds());
	}
	else
	{
		ReturnToBase(GetWorld()->GetDeltaSeconds());
	}
}

void AHazardActor::MoveTowardsPlayer(float DeltaTime)
{
	if(!CachedPlayer) return;

	float Speed = Config ? Config->MoveSpeed : 150.0f;

	FVector Direction = (CachedPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AHazardActor::ReturnToBase(float DeltaTime)
{
	float Speed = 2.0f;
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), InitialLocation, DeltaTime, Speed);
	SetActorLocation(NewLocation);
}

void AHazardActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bIsActive) return;

	if(!bCanApplyDamage) return;

	AEscapeExtractionCharacter* Player = Cast<AEscapeExtractionCharacter>(OtherActor);
	if(!Player) return;

	ApplyDamageToPlayer(Player);
}

void AHazardActor::ApplyDamageToPlayer(AActor* Player)
{
	if(!Config) return;

	UGameplayStatics::ApplyDamage(
		Player,
		Config->DamageAmount,
		nullptr,
		this,
		UDamageType::StaticClass()
	);

	bCanApplyDamage = false;
	GetWorldTimerManager().SetTimer(
		DamageCooldownTimer,
		this,
		&AHazardActor::ResetDamageCooldown,
		Config->DamageCooldown,
		false
	);
}

void AHazardActor::ResetDamageCooldown()
{
	bCanApplyDamage = true;
}

void AHazardActor::UpdateVisualState()
{
	if(bIsActive && ActiveMaterial)
	{
		MeshComponent->SetMaterial(0, ActiveMaterial);
	}
	else if(!bIsActive && InactiveMaterial)
	{
		MeshComponent->SetMaterial(0, InactiveMaterial);
	}
}
