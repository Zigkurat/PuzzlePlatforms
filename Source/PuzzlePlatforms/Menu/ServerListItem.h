// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListItem.generated.h"

USTRUCT()
struct FServerData {
	GENERATED_BODY()

	FString Name;
	FString HostUsername;
	uint32 CurrentPlayers;
	uint32 MaxPlayers;
};

UCLASS()
class PUZZLEPLATFORMS_API UServerListItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *HostUsername;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *PlayerSlots;

	UPROPERTY(BlueprintReadOnly)
	bool IsSelected = false;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton *SelectButton;

	UPROPERTY()
	class UMainMenu *Parent;

	uint32 Index;

public:
	void Setup(class UMainMenu *InParent, uint32 InIndex);

private:
	UFUNCTION()
	void OnSelectButtonClicked();
};
