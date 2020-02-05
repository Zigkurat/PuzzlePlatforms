// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerListItem.h"
#include "Components/Button.h"
#include "MainMenu.h"

void UServerListItem::Setup(class UMainMenu *InParent, uint32 InIndex) {
    Parent = InParent;
    Index = InIndex;
    SelectButton->OnClicked.AddDynamic(this, &UServerListItem::OnSelectButtonClicked);
}

void UServerListItem::OnSelectButtonClicked() {
    Parent->SelectIndex(Index);
}