// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WalkableDetector.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UWalkableDetector::UWalkableDetector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWalkableDetector::BeginPlay()
{
	Super::BeginPlay();

    Owner = GetOwner();
	// ...
	
}


// Called every frame
void UWalkableDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UWalkableDetector::CanWalkThere(const WalkDirection WalkDirection)
{
    FVector Start;
    FVector End;

    FHitResult HitToGround;
    GetWorld()->LineTraceSingleByChannel(HitToGround, Owner->GetActorLocation(), Owner->GetActorLocation() - FVector(0.f, 0.f, 1000.f), ECC_Visibility);
    float DistanceToGround = Owner->GetActorLocation().Z - HitToGround.ImpactPoint.Z;

    switch (WalkDirection)
    {
    case WalkDirection::AWAY:
        Start = DetectorStartPointAway + Owner->GetActorLocation();
        End = Start + FVector(0.f, 0.f, -50.f - DistanceToGround);
        break;
    case WalkDirection::TOWARD:
        Start = DetectorStartPointToward + Owner->GetActorLocation();
        End = Start + FVector(0.f, 0.f, -50.f - DistanceToGround);
        break;
    case WalkDirection::LEFT:
    case WalkDirection::RIGHT:
        Start = GetOwner()->GetActorLocation();
        End = GetOwner()->GetActorLocation() + GetForwardVector() * 50.0;
        break;
    }

    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
    DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(5);

    FHitResult Hit;
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic);

    if (!Hit.bBlockingHit)
    {
        return false;
    }
    else
    {
        return true;
    }
}

