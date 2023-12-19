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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* GlideAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* DashAction;

    UWalkableDetector* WalkableDetectorComponent;
    USkeletalMeshComponent* SkeletalMeshComponent;
    UCharacterMovementComponent* CharacterMovementComponent;

    void Move(const FInputActionValue& Value);
    void Glide(const FInputActionValue& Value);
    void StopGlide(const FInputActionValue& Value);
    void Dash(const FInputActionValue& Value);
    void ResetDash();

    const FRotator FacingRight = FRotator(0, 0, 0);
    const FRotator FacingLeft = FRotator(0, 180, 0);
    const FVector XAxis = FVector(1.f, 0.f, 0.f);
    const FVector YAxis = FVector(0.f, 1.f, 0.f);
    const FVector ZAxis = FVector(0.f, 0.f, 1.f);

    float OriginalGravityScale;
    float OriginalAirControl;

    bool bIsGliding = false;

    bool bIsDashing = false;
    FTimerHandle DashTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
