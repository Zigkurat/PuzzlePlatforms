// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MenuWidget.h"
#include "Menu/MainMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("New Session");

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

    IOnlineSubsystem *OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem) {
        SessionInterface = OnlineSubsystem->GetSessionInterface();
        if (SessionInterface.IsValid()) {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);
        }
    }
}

void UPuzzlePlatformsGameInstance::LoadMainMenu() {
    if (MainMenuClass) {
        MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);

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

void UPuzzlePlatformsGameInstance::JoinButtonClicked(uint32 Index) {
    Join(Index);
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

void UPuzzlePlatformsGameInstance::RefreshServerList() {
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    if (SessionSearch.IsValid()) {
        SessionSearch->bIsLanQuery = true;
        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
}

void UPuzzlePlatformsGameInstance::Host() {
    if (SessionInterface.IsValid()) {
        auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
        if (ExistingSession) {
            SessionInterface->DestroySession(SESSION_NAME);
        } else {
            CreateSession();
        }
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

void UPuzzlePlatformsGameInstance::Join(uint32 Index) {
    if (SessionInterface.IsValid() && SessionSearch.IsValid()) {
        if (MainMenu) {
            MainMenu->Teardown();
        }

        SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
    }
}

void UPuzzlePlatformsGameInstance::CreateSession() {
    if (SessionInterface.IsValid()) {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = true;
        SessionSettings.NumPublicConnections = 2;
        SessionSettings.bShouldAdvertise = true;
        SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
    }
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success) {
    if (Success) {
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
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success) {
    if (Success) {
        CreateSession();
    }
}

void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool Success) {
    if (SessionSearch.IsValid() && Success && MainMenu) {
        TArray<FString> ServerNames;
        ServerNames.Add("First");
        ServerNames.Add("Second");
        ServerNames.Add("Third");
        ServerNames.Add("Fourth");
        for (const auto &SearchResult : SessionSearch->SearchResults) {
            ServerNames.Add(SearchResult.GetSessionIdStr());
        }

        MainMenu->SetServerList(ServerNames);
    }
}

void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
    UE_LOG(LogTemp, Warning, TEXT("JoinSessionComplete"));
    if (SessionInterface.IsValid()) {
        UE_LOG(LogTemp, Warning, TEXT("Session Is Valid"));
        FString Address;
        if (SessionInterface->GetResolvedConnectString(SessionName, Address)) {
            UE_LOG(LogTemp, Warning, TEXT("Session Resolved String"));
            APlayerController *PlayerController = GetFirstLocalPlayerController();
            if (PlayerController) {
                UE_LOG(LogTemp, Warning, TEXT("Player Controller Found"));
                PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
            }
        }
    }
}