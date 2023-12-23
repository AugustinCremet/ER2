// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManager.h"
#include "AbilitySystemGlobals.h"

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
	
    //if (AbilitySystemComponent)
    //{
    //    for (TSubclassOf<UGameplayAbility> Ability : Abilities)
    //    {
    //        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
    //    }

    //    TArray<FGameplayAbilitySpec> AbilitySpecs = AbilitySystemComponent->GetActivatableAbilities();

    //    for (FGameplayAbilitySpec& AbilitySpec : AbilitySpecs)
    //    {
    //        Handles.Add(AbilitySpec.Handle);
    //    }

    //}
}

TSubclassOf<UGameplayAbility> UAbilityManager::GetTheRightAbility(FGameplayTag GameplayTag)
{
    TSubclassOf<UGameplayAbility> AbilityFound = NULL;
    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(GameplayTag);

    for (TSubclassOf<UGameplayAbility> Ability : Abilities)
    {
        UGameplayAbility* abilitytogettag = Ability.GetDefaultObject();
        if(TagContainer.HasAny(abilitytogettag->AbilityTags))
        {
            AbilityFound = Ability;
            break;
        }
    }

    return AbilityFound;
}

void UAbilityManager::GiveAbility(FGameplayTag GameplayTag)
{
    if (AbilitySystemComponent)
    {
        TSubclassOf<UGameplayAbility> Ability = GetTheRightAbility(GameplayTag);
        if (Ability)
        {
            FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
            Abilities.Add(Ability);
            Handles.Add(Handle);
        }
    }
}

void UAbilityManager::ActivateAbility(FGameplayTag GameplayTag)
{
    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(GameplayTag);
    TArray<FGameplayAbilitySpecHandle> AbilitiesWithTag;
    AbilitySystemComponent->FindAllAbilitiesWithTags(Handles, TagContainer);

    for (FGameplayAbilitySpecHandle Handle : Handles)
    {
        if(Handle.IsValid())
        {
            AbilitySystemComponent->TryActivateAbility(Handle, true);
            break;
        }
    }
}

// Called every frame
void UAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

