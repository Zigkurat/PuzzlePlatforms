// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "Engine/World.h"

bool UInGameMenu::Initialize() {
    if (Super::Initialize()) {
        if (QuitButton) {
            QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitButtonClicked);
        }
        if (CancelButton) {
            CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelButtonClicked);
        }

        return true;
    } else {
        return false;
    }
}

void UInGameMenu::QuitButtonClicked() {
    if (MenuInterface) {
        Teardown();
        MenuInterface->QuitButtonClicked();
    }
}

void UInGameMenu::CancelButtonClicked() {
    Teardown();
}