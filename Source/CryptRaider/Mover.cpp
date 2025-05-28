// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();	
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ShouldMove)
	{
		GetOwner()->SetActorLocation(GetMoveDirection(DeltaTime));
	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

FVector UMover::GetMoveDirection(float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = OriginalLocation + MoveOffset;
	float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;
	return FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
}