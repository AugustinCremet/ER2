// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ErAttributeSet.h"

UErAttributeSet::UErAttributeSet()
{
    InitHealth(30.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetHealthAttribute(), Health, "Attribute.Health"));
    InitMaxHealth(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetMaxHealthAttribute(), MaxHealth, "Attribute.MaxHealth"));
    InitRage(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetRageAttribute(), Rage, "Attribute.Rage"));
    InitMaxRage(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetMaxRageAttribute(), MaxRage, "Attribute.MaxRage"));
}

void UErAttributeSet::SetAttributesValue(FGameplayTag Tag, float Value)
{
    for (FAttributeNTag Attribute : AttributesDataNTag)
    {
        if (Attribute.Tag == Tag)
        {
            GetOwningAbilitySystemComponent()->SetNumericAttributeBase(Attribute.Attribute, Value);
            break;
        }
    }
}

float UErAttributeSet::GetAttributeValue(FGameplayAttribute Attribute)
{
    auto Value = GetOwningAbilitySystemComponent()->GetNumericAttribute(Attribute);
    return Value;
}

FAttributeNTag::FAttributeNTag(FGameplayAttribute NewAttribute, FGameplayAttributeData NewAttributeData, FString String)
{
    Attribute = NewAttribute;
    AttributeData = NewAttributeData;
    Tag = FGameplayTag::RequestGameplayTag(FName(String));
}
