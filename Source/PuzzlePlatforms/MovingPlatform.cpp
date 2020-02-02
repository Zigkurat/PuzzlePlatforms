// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
    Super::BeginPlay();

    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    StartLocation = GetActorLocation();
    EndLocation = GetActorLocation() + TargetLocation;
}

void AMovingPlatform::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (HasAuthority()) {
        if (ActiveTriggers > 0) {
            FVector Location = GetActorLocation();
            FVector Direction = (EndLocation - Location).GetSafeNormal();
            Location += Direction * (MoveSpeed * DeltaTime);
            SetActorLocation(Location);

            FVector NextDirection = (EndLocation - Location).GetSafeNormal();
            if (FVector::DotProduct(Direction, NextDirection) == -1) {
                FVector TempVector = StartLocation;
                StartLocation = EndLocation;
                EndLocation = TempVector;
            }
        }
    }
}

void AMovingPlatform::AddActiveTrigger() {
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger() {
    ActiveTriggers--;
}