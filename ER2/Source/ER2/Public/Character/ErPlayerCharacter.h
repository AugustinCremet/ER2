// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ErCharacterBase.h"
#include "InputActionValue.h"
#include "Component/WalkableDetector.h"
#include "Abilities/GameplayAbility.h"
#include "Component/AbilityManager.h"
#include "UObject/Object.h"
#include "ErPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ER2_API AErPlayerCharacter : public AErCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AErPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UAbilitySystemComponent* AbilitySystemComponent;
    FGameplayAbilitySpecHandle Handle;
    UAbilityManager* AbilityManager;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TSubclassOf<UGameplayAbility> YourAbilityClass;
    UGameplayAbility* NewAbilityInstance;

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    bool bGiveAbility;

    UWalkableDetector* WalkableDetectorComponent;
    USkeletalMeshComponent* SkeletalMeshComponent;
    UCharacterMovementComponent* CharacterMovementComponent;

    void Move(const FInputActionValue& Value);
    void StopMove(const FInputActionValue& Value);
    void Jump(const FInputActionValue& Value);
    void Glide(const FInputActionValue& Value);
    void StopGlide(const FInputActionValue& Value);
    void Dash(const FInputActionValue& Value);

    const FRotator FacingRight = FRotator(0, 0, 0);
    const FRotator FacingLeft = FRotator(0, 180.0f, 0);
    const FVector XAxis = FVector(1.0f, 0.0f, 0.0f);
    const FVector YAxis = FVector(0.0f, 1.0f, 0.0f);
    const FVector ZAxis = FVector(0.0f, 0.0f, 1.0f);
    FVector InitialLocation;
    FVector TargetLocation;

    float OriginalGravityScale;
    float OriginalAirControl;
    float DashDistance = 1000.0f;
    float DashDuration = 0.1f;
    float DashTimer = 0.0f;

    bool bIsMoving = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
