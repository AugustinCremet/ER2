// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WalkableDetector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ER2_API UWalkableDetector : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWalkableDetector();
    bool CanGo;
    bool GetCanGo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    bool IsThereAHit();		
};
