// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManager.h"

// Sets default values for this component's properties
UAbilityManager::UAbilityManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UAbilityManager::BeginPlay()
{
	Super::BeginPlay();

    AbilitySystemComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	
}

void UAbilityManager::GiveAbility()
{
    NewAbilityInstance = YourAbilityClass.GetDefaultObject();

    if (AbilitySystemComponent && NewAbilityInstance)
    {
        Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(YourAbilityClass, 1, 0));
        AbilitySystemComponent->InitAbilityActorInfo(GetOwner(), GetOwner());
    }

    if (AbilitySystemComponent && AbilitySystemComponent->TryActivateAbility(Handle, true))
    {
        AbilitySystemComponent->TryActivateAbility(Handle, true);

        //if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Tests.GenericTag"))))
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Has the tag"));
        //}

        //AbilitySystemComponent->ClearAbility(Handle);

        //if (!AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Tests.GenericTag"))))
        //{
        //    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Tag got removed"));
        //}
    }
}

// Called every frame
void UAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

