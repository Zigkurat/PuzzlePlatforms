// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton *QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton *CancelButton;

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();
};
