// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ErCharacterBase.h"

// Sets default values
AErCharacterBase::AErCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

UAbilitySystemComponent* AErCharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AErCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

