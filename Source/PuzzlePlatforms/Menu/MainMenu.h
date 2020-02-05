// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	UMainMenu(const FObjectInitializer &ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher *MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget *MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget *JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget *ServerListMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton *HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableText *AddressTextBox;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinServerListMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelServerListMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget *ServerList;

private:
	TSubclassOf<class UUserWidget>  ServerListItemClass;

	TOptional<uint32> SelectedIndex;

public:
	void SetServerList(TArray<FString> ServerNames);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

	UFUNCTION()
	void JoinJoinMenuButtonClicked();
	
	UFUNCTION()
	void CancelJoinMenuButtonClicked();

	UFUNCTION()
	void JoinServerListMenuButtonClicked();

	UFUNCTION()
	void CancelServerListMenuButtonClicked();
};
