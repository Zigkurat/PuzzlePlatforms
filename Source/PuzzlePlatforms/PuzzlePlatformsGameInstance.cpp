// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) {
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (MainMenuBPClass.Class)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init() {
    Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu() {
    if (MainMenuClass) {
        auto MenuWidget = CreateWidget<UMainMenu>(this, MainMenuClass);

        if (MenuWidget) {
            MenuWidget->AddToViewport();
            MenuWidget->SetMainMenuInterface(this);

            APlayerController *PlayerController = GetFirstLocalPlayerController();
            if (PlayerController) {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;
            }
        }
    }
}

void UPuzzlePlatformsGameInstance::HostButtonClicked() {
    Host();
}

void UPuzzlePlatformsGameInstance::JoinButtonClicked() {

}

void UPuzzlePlatformsGameInstance::Host() {
    UEngine *Engine = GetEngine();
    if (Engine) {
        Engine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString("Hosting"));
    }

    UWorld *World = GetWorld();
    if (World) {
        World->ServerTravel("/Game/Maps/Puzzle?listen");
    }
}

void UPuzzlePlatformsGameInstance::Join(const FString &Address) {
    UEngine *Engine = GetEngine();

    if (Engine) {
        Engine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
    }

    APlayerController *PlayerController = GetFirstLocalPlayerController();
    if (PlayerController) {
        PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
    }
}