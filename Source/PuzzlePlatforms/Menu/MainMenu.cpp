// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "ServerListItem.h"

UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer) {
    static ConstructorHelpers::FClassFinder<UUserWidget> ServerListItemBPClass(TEXT("/Game/Menu/WBP_ServerListItem"));
	if (ServerListItemBPClass.Class)
	{
		ServerListItemClass = ServerListItemBPClass.Class;
	}
}

void UMainMenu::SetServerList(TArray<FString> ServerNames) {
    if (ServerList) {
        ServerList->ClearChildren();
        uint32 Index = 0;
        for (const auto &ServerName : ServerNames) {
            auto ServerListItem = CreateWidget<UServerListItem>(this, ServerListItemClass);
            if (ServerListItem) {
                ServerListItem->ServerName->SetText(FText::FromString(ServerName));
                ServerListItem->Setup(this, Index);
                
                ServerList->AddChild(ServerListItem);

                ++Index;
            }
        }
    }
}

void UMainMenu::SelectIndex(uint32 Index) {
    SelectedIndex = Index;

    for (uint32 i = 0; i < ServerList->GetChildrenCount(); i++) {
        UServerListItem *Item = Cast<UServerListItem>(ServerList->GetChildAt(i));
        if (Item) {
            Item->IsSelected = i == Index;
        }
    }
}

bool UMainMenu::Initialize() {
    if (Super::Initialize()) {
        if (HostButton) {
            HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostButtonClicked);
        }
        if (JoinButton) {
            JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinButtonClicked);
        }
        if (ExitButton) {
            ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitButtonClicked);
        }
        if (JoinJoinMenuButton) {
            JoinJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinJoinMenuButtonClicked);
        }
        if (CancelJoinMenuButton) {
            CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenuButtonClicked);
        }
        if (JoinServerListMenuButton) {
            JoinServerListMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServerListMenuButtonClicked);
        }
        if (CancelServerListMenuButton) {
            CancelServerListMenuButton->OnClicked.AddDynamic(this, &UMainMenu::CancelServerListMenuButtonClicked);
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
    if (MenuSwitcher && ServerListMenu) {
        MenuSwitcher->SetActiveWidget(ServerListMenu);

        if (MenuInterface) {
            MenuInterface->RefreshServerList();
        }
    }
}

void UMainMenu::ExitButtonClicked() {
    if (MenuInterface) {
        MenuInterface->ExitButtonClicked();
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

void UMainMenu::JoinServerListMenuButtonClicked() {
    if (SelectedIndex.IsSet() && MenuInterface) {
        MenuInterface->JoinButtonClicked(SelectedIndex.GetValue());
    }
}

void UMainMenu::CancelServerListMenuButtonClicked() {
    if (MenuSwitcher && MainMenu) {
        MenuSwitcher->SetActiveWidget(MainMenu);
    }
}