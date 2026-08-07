// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyPickup.h"
#include "EscapeExtractionCharacter.h"

void AKeyPickup::ApplyEffect(AEscapeExtractionCharacter *Character)
{
    if(Character)
    {
        Character->AddItem(KeyCount);
    }
}
