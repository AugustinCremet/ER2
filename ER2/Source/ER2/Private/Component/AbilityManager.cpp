// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityManager.h"
#include "AbilitySystemGlobals.h"
#include <Misc/OutputDeviceNull.h>
#include "Containers/UnrealString.h"
#include "Player/ErPlayerState.h"


class APawn;
class APlayerState;

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

    APawn* Pawn = Cast<APawn>(GetOwner());
    AErPlayerState* PlayerState = Cast<AErPlayerState>(Pawn->GetPlayerState());
    AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
    //GiveAbility("Ability.Dash");
    GiveAbility("Ability.Jump");
    //GiveAbility("Ability.Jump.Double");
    //GiveAbility("Ability.Glide");   
}

TSubclassOf<UGameplayAbility> UAbilityManager::GetGameplayAbility(FGameplayTag GameplayTag)
{
    TSubclassOf<UGameplayAbility> AbilityFound = NULL;

    for (TSubclassOf<UGameplayAbility> Ability : Abilities)
    {
        UGameplayAbility* Abilitytogettag = Ability.GetDefaultObject();
        FGameplayTagContainer TagOfThisAbility = Abilitytogettag->AbilityTags;
        if(TagOfThisAbility.HasTagExact(GameplayTag))
        {
            AbilityFound = Ability;
            break;
        }
    }

    return AbilityFound;
}

FGameplayAbilitySpecHandle UAbilityManager::GetGameplayAbilitySpecHandle(FGameplayTag GameplayTag)
{
    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(GameplayTag);
    TArray<FGameplayAbilitySpecHandle> AbilitiesWithTag;
    AbilitySystemComponent->FindAllAbilitiesWithTags(Handles, TagContainer);

    for (FGameplayAbilitySpecHandle Handle : Handles)
    {
        if (Handle.IsValid())
        {
            return Handle;
        }
    }

    return FGameplayAbilitySpecHandle();
}

FGameplayTag UAbilityManager::StringToGameplayTag(FString String)
{
    return FGameplayTag::RequestGameplayTag(FName(String));
}

void UAbilityManager::GiveAbility(FString String)
{
    FGameplayTag GameplayTag = StringToGameplayTag(String);

    if (AbilitySystemComponent)
    {
        TSubclassOf<UGameplayAbility> Ability = GetGameplayAbility(GameplayTag);
        if (Ability)
        {
            FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
            AbilitiesTag.Add(GameplayTag);
            Handles.Add(Handle);
        }
    }
}

void UAbilityManager::GiveAbility(FGameplayTag GameplayTag)
{
    if (AbilitySystemComponent)
    {
        TSubclassOf<UGameplayAbility> Ability = GetGameplayAbility(GameplayTag);
        if (Ability)
        {
            FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
            AbilitiesTag.Add(GameplayTag);
            Handles.Add(Handle);
        }
    }
}


bool UAbilityManager::ActivateAbility(FString String)
{
    FGameplayTag GameplayTag = StringToGameplayTag(String);
    TSubclassOf<UGameplayAbility> Ability = GetGameplayAbility(GameplayTag);
    FGameplayAbilitySpecHandle Handle = GetGameplayAbilitySpecHandle(GameplayTag);

    if (Handle.IsValid() && AbilitySystemComponent->TryActivateAbility(Handle, true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void UAbilityManager::StopAbility(FString String)
{
    FGameplayTag GameplayTag = StringToGameplayTag(String);
    TSubclassOf<UGameplayAbility> Ability = GetGameplayAbility(GameplayTag);

    if (Ability)
    {
        UGameplayAbility* Instance = Ability.GetDefaultObject();
        AbilitySystemComponent->CancelAbility(Instance);
    }
}

bool UAbilityManager::HasTag(FString String)
{
    FGameplayTag GameplayTag = StringToGameplayTag(String);
    return AbilitySystemComponent->HasMatchingGameplayTag(GameplayTag);
}

// Called every frame
void UAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

