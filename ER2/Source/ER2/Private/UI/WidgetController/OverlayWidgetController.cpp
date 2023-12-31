// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ErAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UErAttributeSet* ErAttributeSet = CastChecked<UErAttributeSet>(AttributeSet);
    OnHealthChanged.Broadcast(ErAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(ErAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const UErAttributeSet* ErAttributeSet = CastChecked<UErAttributeSet>(AttributeSet);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        ErAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
        ErAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
    OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
    OnMaxHealthChanged.Broadcast(Data.NewValue);
}
