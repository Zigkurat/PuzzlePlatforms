// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Menu/MainMenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

private:
	TSubclassOf<class UUserWidget> MainMenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu *MainMenu;

	class UMenuWidget *InGameMenu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, exec)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, exec)
	void LoadInGameMenu();

	void StartSession();

protected:
	virtual void HostButtonClicked(const FString &Name) override;

	virtual void JoinButtonClicked(const FString &Address) override;

	virtual void JoinButtonClicked(uint32 Index) override;

	virtual void QuitButtonClicked() override;

	virtual void ExitButtonClicked() override;

	virtual void RefreshServerList() override;

private:
	UFUNCTION(exec)
	void Host(const FString &Name); 

	UFUNCTION(exec)
	void Join(const FString &Address);

	void Join(uint32 Index);

	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionsComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
