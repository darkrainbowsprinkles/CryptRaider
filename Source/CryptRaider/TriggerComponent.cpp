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

    if(Mover == nullptr)
    {
        return;
    }

    TArray<AActor*> Actors = GetAcceptableActors();

    if (Actors.Num() == 0)
    {
        Mover->SetShouldMove(false);
        return;
    }

    for (AActor* Actor : Actors)
    {
        if (Actor)
        {
            UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
            if (Component)
            {
                Component->SetSimulatePhysics(false);
            }
            Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
    Mover->SetShouldMove(true);
}

void UTriggerComponent::SetMover(UMover *NewMover)
{   
    Mover = NewMover;
}

TArray<AActor*> UTriggerComponent::GetAcceptableActors() const
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);

    // Early out if counts don't match
    if (OverlappingActors.Num() != AcceptableTags.Num())
    {
        return {};
    }

    TArray<AActor*> MatchedActors;
    TArray<FName> TagsToMatch = AcceptableTags;

    // For each actor, try to match a unique tag
    for (AActor* Actor : OverlappingActors)
    {
        if (!Actor || Actor->ActorHasTag("Grabbed"))
        {
            return {};
        }

        bool FoundTag = false;
        for (int32 i = 0; i < TagsToMatch.Num(); ++i)
        {
            if (Actor->ActorHasTag(TagsToMatch[i]))
            {
                MatchedActors.Add(Actor);
                TagsToMatch.RemoveAt(i);
                FoundTag = true;
                break;
            }
        }
        if (!FoundTag)
        {
            return {};
        }
    }

    // If all tags matched, return actors
    if (MatchedActors.Num() == AcceptableTags.Num())
    {
        return MatchedActors;
    }
    return {};
}