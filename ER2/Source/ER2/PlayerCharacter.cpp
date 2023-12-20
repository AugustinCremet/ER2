// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
    SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
    CharacterMovementComponent = FindComponentByClass<UCharacterMovementComponent>();

    if (CharacterMovementComponent)
    {
        OriginalGravityScale = CharacterMovementComponent->GravityScale;
        OriginalAirControl = CharacterMovementComponent->AirControl;
    }
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    if (bIsDashing)
        return;

    bIsMoving = true;

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

void APlayerCharacter::StopMove(const FInputActionValue& Value)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("STOPPP"));
    bIsMoving = false;
}

void APlayerCharacter::Glide(const FInputActionValue& Value)
{
    if (!bIsGliding && JumpCurrentCount == 3)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, TEXT("Glide!"));
        
        bIsGliding = true;
        CharacterMovementComponent->Velocity = FVector(CharacterMovementComponent->Velocity.X, CharacterMovementComponent->Velocity.Y, 0);
        CharacterMovementComponent->GravityScale = 0.07f;
        CharacterMovementComponent->AirControl = 0.7f;
    }
}

void APlayerCharacter::StopGlide(const FInputActionValue& Value)
{
    if (CharacterMovementComponent)
    {
        if (bIsGliding)
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, TEXT("Stop glide"));
            bIsGliding = false;
            CharacterMovementComponent->GravityScale = OriginalGravityScale;
            CharacterMovementComponent->AirControl = OriginalAirControl;
        }
    }
}

void APlayerCharacter::Dash(const FInputActionValue& Value)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Start dash"));

    if (!bIsDashing && bIsMoving)
    {
        CharacterMovementComponent->DisableMovement();
        FVector DashDirection = CharacterMovementComponent->GetLastInputVector().GetSafeNormal();
        InitialLocation = GetActorLocation();
        TargetLocation = InitialLocation + DashDirection * DashDistance;
        bIsDashing = true;
        DashTimer = 0.0f;
    }
}

void APlayerCharacter::ResetDash()
{
    bIsDashing = false;
    DashTimerHandle.Invalidate();

    if (CharacterMovementComponent)
    {
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    }
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CharacterMovementComponent)
    {
        if (bIsGliding && !CharacterMovementComponent->IsFalling())
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, TEXT("On ground"));
            bIsGliding = false;
            CharacterMovementComponent->GravityScale = OriginalGravityScale;
            CharacterMovementComponent->AirControl = OriginalAirControl;
        }

        if (bIsDashing)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Dashing"));
            DashTimer += DeltaTime;
            float Alpha = FMath::Clamp(DashTimer / DashDuration, 0.0f, 1.0f);
            FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, Alpha);

            FHitResult HitResult;
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(this); // Ignore the current actor during the trace

            if (GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(10.0f), CollisionParams))
            {
                // Collision detected, adjust dash distance to stop at hit location
                TargetLocation = HitResult.Location;
                DashDuration = DashTimer * Alpha; // Adjust duration based on current progress
            }
            else
            {
                SetActorLocation(NewLocation);
            }

            if (Alpha >= 1.0f)
            {
                // Dash completed
                bIsDashing = false;
                CharacterMovementComponent->SetMovementMode(MOVE_Walking);
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Dash done"));
                // Perform any actions after the dash is complete
            }
        }
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMove);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(GlideAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Glide);
        EnhancedInputComponent->BindAction(GlideAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopGlide);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::Dash);
    }
}

