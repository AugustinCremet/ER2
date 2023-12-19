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
    enum WalkDirection
    {
        AWAY,
        LEFT,
        TOWARD,
        RIGHT
    };


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FVector DetectorStartPointToward;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FVector DetectorStartPointAway;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FVector DetectorStartLeftRight;

    AActor* Owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    bool CanWalkThere(const WalkDirection Direction);		
};
