// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class PUZZLEPLATFORMS_API IMainMenuInterface
{
	GENERATED_BODY()

public:
	virtual void HostButtonClicked() = 0;

	virtual void JoinButtonClicked() = 0;
};
