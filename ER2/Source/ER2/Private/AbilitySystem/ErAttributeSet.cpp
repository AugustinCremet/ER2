// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ErAttributeSet.h"

UErAttributeSet::UErAttributeSet()
{
    InitHealth(100.0f);
    InitMaxHealth(100.0f);
    InitMana(100.0f);
    InitMaxMana(100.0f);
}

//void UErAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
//{
//    GAMEPLAYATTRIBUTE_REPNOTIFY(UErAttributeSet, Health, OldHealth);
//}
