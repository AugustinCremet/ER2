// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ErHUD.generated.h"

class UErUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class ER2_API AErHUD : public AHUD
{
	GENERATED_BODY()
public:
    UPROPERTY()
    TObjectPtr<UErUserWidget> OverlayWidget;
    UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

    void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UErUserWidget> OverlayWidgetClass;

    UPROPERTY()
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
