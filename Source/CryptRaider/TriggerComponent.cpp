// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* AcceptableActor = GetAcceptableActor();

    if(Mover == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("UMover not found!"));
        return;
    }

    Mover->SetShouldMove(AcceptableActor != nullptr);
}

void UTriggerComponent::SetMover(UMover *NewMover)
{   
    Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;

    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(UnlockTag))
        {
            return Actor;
        }
    }

    return nullptr;
}