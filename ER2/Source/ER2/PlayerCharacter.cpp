// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);

        }
    }

    WalkableDetectorComponent = FindComponentByClass<UWalkableDetector>();
    MeshComponent = FindComponentByClass<USkeletalMeshComponent>();
    if (MeshComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("non null"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("null"));

    }
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D DirectionValue = Value.Get<FVector2D>();

    UInputModifierDeadZone* DeadZone = (UInputModifierDeadZone*)MoveAction->Modifiers[0];
    
    double angle = FMath::RadiansToDegrees(FMath::Atan2(DirectionValue.Y, DirectionValue.X));

    if (GetController() != nullptr && abs(DirectionValue.X) >= DeadZone->LowerThreshold)
    {
        if (WalkableDetectorComponent->CanWalkThere(UWalkableDetector::WalkDirection::LEFT))
        {
            AddMovementInput(XAxis, DirectionValue.X);
            if (DirectionValue.X > 0.0)
                SetActorRotation(FacingRight, ETeleportType::None);
            else
                SetActorRotation(FacingLeft, ETeleportType::None);
        }
    }
    
    if (GetController() != nullptr && abs(DirectionValue.Y) >= DeadZone->LowerThreshold)
    {
        UWalkableDetector::WalkDirection CurrentDirection = DirectionValue.Y > 0.0 ? UWalkableDetector::WalkDirection::TOWARD : UWalkableDetector::WalkDirection::AWAY;

        if (WalkableDetectorComponent->CanWalkThere(CurrentDirection))
        {
            AddMovementInput(YAxis, DirectionValue.Y);
            SetActorRotation(FRotator(0.0, angle, 0.0), ETeleportType::None);
        }
    }
    
    
}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
    ACharacter::Jump();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
    }
}

