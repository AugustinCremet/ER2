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
    TSubclassOf<UGameplayAbility> GetGameplayAbility(FGameplayTag GameplayTag);
    FGameplayAbilitySpecHandle GetGameplayAbilitySpecHandle(FGameplayTag GameplayTag);
    FGameplayTag StringToGameplayTag(FString String);

    UAbilitySystemComponent* AbilitySystemComponent;
    TArray<FGameplayAbilitySpecHandle> Handles;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> Abilities;
    UPROPERTY(BlueprintReadOnly, Category = "Abilities", meta = (BlueprintAssignable))
    TArray<FGameplayTag> AbilitiesTag;
    UGameplayAbility* NewAbilityInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void GiveAbility(FString String);
    UFUNCTION(BlueprintCallable, Category = "AbilityManager")
    void GiveAbility(FGameplayTag GameplayTag);
    UFUNCTION(BlueprintCallable, Category = "AbilityManager")
    bool HasAbility(FGameplayTag GameplayTag);
    bool ActivateAbility(FString String);
    void StopAbility(FString String);
    bool HasTag(FString String);
};
