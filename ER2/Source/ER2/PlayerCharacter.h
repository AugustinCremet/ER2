// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WalkableDetector.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ER2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* PlayerMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* JumpAction;

    UWalkableDetector* WalkableDetectorComponent;
    USkeletalMeshComponent* MeshComponent;

    void Move(const FInputActionValue& Value);
    void Jump(const FInputActionValue& Value);

    const FRotator FacingRight = FRotator(0, 0, 0);
    const FRotator FacingLeft = FRotator(0, 180, 0);
    const FVector XAxis = FVector(1.f, 0.f, 0.f);
    const FVector YAxis = FVector(0.f, 1.f, 0.f);
    const FVector ZAxis = FVector(0.f, 0.f, 1.f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
