// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Menu/MainMenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

private:
	TSubclassOf<class UUserWidget> MainMenuClass;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, exec)
	void LoadMenu();

protected:
	virtual void HostButtonClicked() override;

	virtual void JoinButtonClicked() override;

private:
	UFUNCTION(exec)
	void Host();

	UFUNCTION(exec)
	void Join(const FString &Address);
};
