// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ErAttributeSet.h"

UErAttributeSet::UErAttributeSet()
{
    InitHealth(30.0f);
    InitMaxHealth(100.0f);
    InitMana(100.0f);
    InitMaxMana(100.0f);
}

void UErAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    FString FloatAsString = FString::SanitizeFloat(NewValue);
    FString DebugMessage = FString::Printf(TEXT("Your float variable is: %s"), *FloatAsString);
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, DebugMessage, false);
}
