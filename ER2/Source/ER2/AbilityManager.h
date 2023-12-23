// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "AbilityManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ER2_API UAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    TSubclassOf<UGameplayAbility> GetTheRightAbility(FGameplayTag GameplayTag);

    UAbilitySystemComponent* AbilitySystemComponent;
    TArray<FGameplayAbilitySpecHandle> Handles;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> Abilities;
    UGameplayAbility* NewAbilityInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void GiveAbility(FGameplayTag GameplayTag);
    void ActivateAbility(FGameplayTag GameplayTag);
};
