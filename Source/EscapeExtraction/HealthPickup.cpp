// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "EscapeExtractionCharacter.h"
#include "HealthComponent.h"

void AHealthPickup::ApplyEffect(AEscapeExtractionCharacter *Character)
{
    if (!Character || !Character->HealthComponent) return;

    if (Character->HealthComponent->CurrentHealth < Character->HealthComponent->MaxHealth)
    {
        Character->HealthComponent->Heal(HealAmount);
        Destroy();
    }
}
