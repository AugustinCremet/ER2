// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

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
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D DirectionValue = Value.Get<FVector2D>();
    const FRotator FacingRight = FRotator(0, 0, 0);
    const FRotator FacingLeft = FRotator(0, 180, 0);
    const FRotator FacingBack = FRotator(0, 270, 0);
    const FRotator FacingFront = FRotator(0, 90, 0);
    const FVector XAxis = FVector(1.f, 0.f, 0.f);
    const FVector YAxis = FVector(0.f, -1.f, 0.f);

    UInputModifierDeadZone* test = (UInputModifierDeadZone*)MoveAction->Modifiers[0];

    if (GetController() != nullptr && abs(DirectionValue.X) >= test->LowerThreshold)
    {
        AddMovementInput(XAxis, DirectionValue.X);
        if (DirectionValue.X < 0.f)
        {
            SetActorRotation(FacingLeft, ETeleportType::None);
        }
        else
        {
            SetActorRotation(FacingRight, ETeleportType::None);
        }

    }
    
    if (GetController() != nullptr && abs(DirectionValue.Y) >= test->LowerThreshold)
    {
        AddMovementInput(YAxis, DirectionValue.Y);
        if (DirectionValue.Y < 0.f)
        {
            SetActorRotation(FacingFront, ETeleportType::None);
        }
        else
        {
            SetActorRotation(FacingBack, ETeleportType::None);
        }
    }
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
    }
}

