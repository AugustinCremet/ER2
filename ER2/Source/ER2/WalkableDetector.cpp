// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkableDetector.h"
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

bool UWalkableDetector::GetCanGo()
{
    return false;
}


// Called when the game starts
void UWalkableDetector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWalkableDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //FVector Start = GetComponentLocation() + FVector(0, 50, 0);
    //FVector End = Start + FVector(0, 0, -200);
    //DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
    //DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

    //FCollisionShape Sphere = FCollisionShape::MakeSphere(5);
    //
    //FHitResult Hit;
    //GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic);

    //if (!Hit.bBlockingHit)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("NO hit"));
    //    CanGo = false;
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("HITTTTT"));
    //    CanGo = true;
    //}
}

bool UWalkableDetector::IsThereAHit()
{
    FVector Start = GetComponentLocation() + FVector(0, 50, 0);
    FVector End = Start + FVector(0, 0, -200);
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
    DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(5);

    FHitResult Hit;
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic);

    if (!Hit.bBlockingHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("NO hit"));
        return false;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("HITTTTT"));
        return true;
    }
}

