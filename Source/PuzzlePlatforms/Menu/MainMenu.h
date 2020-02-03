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
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UWidget *MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget *JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton *HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *JoinJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *ExitButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableText *AddressTextBox;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher *MenuSwitcher;

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void JoinJoinMenuButtonClicked();
	
	UFUNCTION()
	void CancelJoinMenuButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
};
