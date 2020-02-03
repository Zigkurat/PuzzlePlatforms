// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Engine/World.h"

bool UMainMenu::Initialize() {
    if (Super::Initialize()) {
        if (HostButton) {
            HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);
        }
        if (JoinButton) {
            JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);
        }
        if (JoinJoinMenuButton) {
            JoinJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinJoinMenuButtonClicked);
        }
        if (CancelJoinMenuButton) {
            CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenuButtonClicked);
        }
        if (ExitButton) {
            ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitButtonClicked);
        }

        return true;
    } else {
        return false;
    }
}

void UMainMenu::HostButtonClicked() {
    if (MenuInterface) {
        MenuInterface->HostButtonClicked();
    }
}

void UMainMenu::JoinButtonClicked() {
    if (MenuSwitcher && JoinMenu) {
        MenuSwitcher->SetActiveWidget(JoinMenu);
    }
}

void UMainMenu::JoinJoinMenuButtonClicked() {
    if (MenuInterface && AddressTextBox) {
        MenuInterface->JoinButtonClicked(AddressTextBox->GetText().ToString());
    }
}

void UMainMenu::CancelJoinMenuButtonClicked() {
    if (MenuSwitcher && MainMenu) {
        MenuSwitcher->SetActiveWidget(MainMenu);
    }
}

void UMainMenu::ExitButtonClicked() {
    if (MenuInterface) {
        MenuInterface->ExitButtonClicked();
    }
}