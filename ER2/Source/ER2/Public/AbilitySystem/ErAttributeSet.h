// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ErAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ER2_API UErAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UErAttributeSet();

    UPROPERTY(BlueprintReadOnly, /*ReplicatedUsing = OnRep_Health,*/ Category = "Vital Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, Health);

    //UFUNCTION()
    //void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, Mana);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, MaxMana);
};
