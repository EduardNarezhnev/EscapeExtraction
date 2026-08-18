// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "EscapeExtractionCharacter.h"
#include "EscapeExtractionGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName("OverlapAllDynamic");

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName("OverlapAllDynamic");
	SphereComponent->SetSphereRadius(100.0f);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnOverlapBegin);
}

void APickupActor::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AEscapeExtractionCharacter* Character = Cast<AEscapeExtractionCharacter>(OtherActor);
	if(!Character) return;

	
	AEscapeExtractionGameMode* GM = GetWorld()->GetAuthGameMode<AEscapeExtractionGameMode>();
	if(GM && GM->GetCurrentState() != EGameState::InProgress) return;

	ApplyEffect(Character);

	if(PickupSound)
	{
		UGameplayStatics::PlaySound2D(this, PickupSound);
	}
}

void APickupActor::ApplyEffect(AEscapeExtractionCharacter *Character)
{

}
