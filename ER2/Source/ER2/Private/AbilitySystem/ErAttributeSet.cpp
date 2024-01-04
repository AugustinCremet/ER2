// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ErAttributeSet.h"

UErAttributeSet::UErAttributeSet()
{
    InitHealth(30.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetHealthAttribute(), "Attribute.Vital.Health"));
    InitMaxHealth(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetMaxHealthAttribute(), "Attribute.Vital.MaxHealth"));
    InitRage(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetRageAttribute(), "Attribute.Vital.Rage"));
    InitMaxRage(100.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetMaxRageAttribute(), "Attribute.Vital.MaxRage"));
    InitDashCD(10.0f);
    AttributesDataNTag.Add(FAttributeNTag(GetDashCDAttribute(), "Attribute.Cooldown.Dash"));
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

FAttributeNTag::FAttributeNTag(FGameplayAttribute NewAttribute, FString String)
{
    Attribute = NewAttribute;
    Tag = FGameplayTag::RequestGameplayTag(FName(String));
}
