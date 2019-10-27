// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Check to make sure everything is still valid and that we are allowed to move
    if (PawnOwner == nullptr || UpdatedComponent == nullptr || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Get and clear the vector from Collider
    FVector DesiredMovementThisFrame = ConsumeInputVector() * DeltaTime * 150.f;
    if (DesiredMovementThisFrame.IsNearlyZero() == false)
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // If we bump into something, slide amond the size of it
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
}