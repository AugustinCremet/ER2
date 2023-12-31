// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameplayEffect.h>
#include "UI/WidgetController/ErWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ER2_API UOverlayWidgetController : public UErWidgetController
{
	GENERATED_BODY()
public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallbacksToDependencies() override;

    UPROPERTY(BlueprintAssignable, Category="Gas|Attributes")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
    FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:
    void HealthChanged(const FOnAttributeChangeData& Data);
    void MaxHealthChanged(const FOnAttributeChangeData& Data);

};
