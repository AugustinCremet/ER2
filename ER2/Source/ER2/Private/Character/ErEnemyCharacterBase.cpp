// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErEnemyCharacterBase.h"
#include <AbilitySystem/ErAbilitySystemComponent.h>
#include <AbilitySystem/ErAttributeSet.h>

AErEnemyCharacterBase::AErEnemyCharacterBase()
{
    AbilitySystemComponent = CreateDefaultSubobject<UErAbilitySystemComponent>("AbilitySystemComponent");
    AttributeSet = CreateDefaultSubobject<UErAttributeSet>("AttributeSet");
}
