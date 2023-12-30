// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ErPlayerState.h"
#include <AbilitySystem/ErAbilitySystemComponent.h>
#include <AbilitySystem/ErAttributeSet.h>

AErPlayerState::AErPlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UErAbilitySystemComponent>("AbilitySystemComponent");
    AttributeSet = CreateDefaultSubobject<UErAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AErPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}
