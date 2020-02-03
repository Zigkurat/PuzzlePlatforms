// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) {
    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (MainMenuBPClass.Class)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}
    static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Menu/WBP_InGameMenu"));
    if (InGameMenuBPClass.Class) {
        InGameMenuClass = InGameMenuBPClass.Class;
    }
}

void UPuzzlePlatformsGameInstance::Init() {
    Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMainMenu() {
    if (MainMenuClass) {
        MainMenu = CreateWidget<UMenuWidget>(this, MainMenuClass);

        if (MainMenu) {
            MainMenu->Setup();
            MainMenu->SetMenuInterface(this);
        }
    }
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu() {
    if (InGameMenuClass) {
        InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
        
        if (InGameMenu) {
            InGameMenu->Setup();
            InGameMenu->SetMenuInterface(this);
        }
    }
}

void UPuzzlePlatformsGameInstance::HostButtonClicked() {
    Host();
}

void UPuzzlePlatformsGameInstance::JoinButtonClicked(const FString &Address) {
    Join(Address);
}

void UPuzzlePlatformsGameInstance::QuitButtonClicked() {
    APlayerController *PlayerController = GetFirstLocalPlayerController();
    if (PlayerController) {
        PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
    }
}

void UPuzzlePlatformsGameInstance::ExitButtonClicked() {
    APlayerController *PlayerController = GetFirstLocalPlayerController();
    if (PlayerController) {
        if (MainMenu) {
            MainMenu->Teardown();
        }
        PlayerController->ConsoleCommand("quit");
    }
}

void UPuzzlePlatformsGameInstance::Host() {
    if (MainMenu) {
        MainMenu->Teardown();
    }

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
    if (MainMenu) {
        MainMenu->Teardown();
    }
    
    UEngine *Engine = GetEngine();

    if (Engine) {
        Engine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
    }

    APlayerController *PlayerController = GetFirstLocalPlayerController();
    if (PlayerController) {
        PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
    }
}