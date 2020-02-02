// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

protected:
	UPROPERTY(EditAnywhere, Category = Movement)
	float MoveSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category = Movement, Meta = (MakeEditWidget))
	FVector TargetLocation;

private:
	FVector StartLocation;

	FVector EndLocation;

	int32 ActiveTriggers = 0;

public:
	void AddActiveTrigger();

	void RemoveActiveTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
