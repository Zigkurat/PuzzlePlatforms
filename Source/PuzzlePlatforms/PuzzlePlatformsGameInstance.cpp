// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer) {

}

void UPuzzlePlatformsGameInstance::Init() {
    Super::Init();

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