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

USTRUCT(BlueprintType)
struct FAttributeNTag
{
    GENERATED_BODY()

    FAttributeNTag() {}
    FAttributeNTag(FGameplayAttribute Attribute, FString String);
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayAttribute Attribute;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Tag;
};
/**
 * 
 */
UCLASS()
class ER2_API UErAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    UErAttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData Rage;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, Rage);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
    FGameplayAttributeData MaxRage;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, MaxRage);

    UPROPERTY(BlueprintReadOnly, Category = "Cooldowns")
    FGameplayAttributeData DashCD;
    ATTRIBUTE_ACCESSORS(UErAttributeSet, DashCD);

    UPROPERTY(BlueprintReadOnly)
    TArray<FAttributeNTag> AttributesDataNTag;

    UFUNCTION(BlueprintCallable)
    void SetAttributesValue(FGameplayTag Tag, float Value);
    UFUNCTION(BlueprintPure)
    float GetAttributeValue(FGameplayAttribute Attribute);
};
