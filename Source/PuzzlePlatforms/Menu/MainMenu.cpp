// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::SetMainMenuInterface(IMainMenuInterface *InterfaceToSet) {
    MainMenuInterface = InterfaceToSet;
}

bool UMainMenu::Initialize() {
    if (Super::Initialize()) {
        if (HostButton) {
            HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);
        }
        if (JoinButton) {
            JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);
        }
        
        return true;
    } else {
        return false;
    }
}

void UMainMenu::HostButtonClicked() {
    if (MainMenuInterface) {
        MainMenuInterface->HostButtonClicked();
    }
}

void UMainMenu::JoinButtonClicked() {
    if (MainMenuInterface) {
        MainMenuInterface->JoinButtonClicked();
    }
}