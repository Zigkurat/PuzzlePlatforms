// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Engine/World.h"

void UMenuWidget::Setup() {
    AddToViewport();

    UWorld *World = GetWorld();
    if (World) {
        APlayerController *PlayerController = World->GetFirstPlayerController(); 
        if (PlayerController) {
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputMode);
            PlayerController->bShowMouseCursor = true;
        }
    }
}

void UMenuWidget::Teardown() {
    RemoveFromViewport();

    UWorld *World = GetWorld();
    if (World) {
        APlayerController *PlayerController = World->GetFirstPlayerController(); 
        if (PlayerController) {
            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
            PlayerController->bShowMouseCursor = false;
        }
    }
}

void UMenuWidget::SetMenuInterface(IMainMenuInterface *Interface) {
    MenuInterface = Interface;
}