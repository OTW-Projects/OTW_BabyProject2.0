// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"

void UUIManager::Initialize(TSubclassOf<UUserWidget> InWidgetClass, APlayerController* OwnerController)
{
	if (!OwnerController)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: Cannot initialize without a valid player controller"));
		return;
	}

	if (!InWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: WidgetClass is null, cannot initialize"));
		return;
	}
	
	// Create the main game widget
	MainGameWidget = CreateWidget<UUserWidget>(OwnerController, InWidgetClass);
	
	if (!MainGameWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: Failed to create main game widget"));
		return;
	}

	CurrentState = EUIState::Hidden;
	UE_LOG(LogTemp, Log, TEXT("UIManager: Initialized successfully"));
}

void UUIManager::UpdateDialogue(const FString& SpeakerName, const FString& DialogueText)
{
	if (CurrentState != EUIState::InGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIManager: Trying to show dialogue while not in game state"));
		return;
	}

	// Call Blueprint event for custom UI update logic
	BP_OnDialogueChanged(SpeakerName, DialogueText);

	UE_LOG(LogTemp, Log, TEXT("UIManager: Updated dialogue - %s: %s"), *SpeakerName, *DialogueText);
}

void UUIManager::UpdateBackground(const FSoftObjectPath& BackgroundImagePath)
{
	// Call Blueprint event for custom background update logic
	BP_OnBackgroundChanged(BackgroundImagePath);

	UE_LOG(LogTemp, Log, TEXT("UIManager: Updated background - %s"), *BackgroundImagePath.ToString());
}

void UUIManager::ShowGameUI()
{
	if (!MainGameWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: MainGameWidget is null, cannot show game UI"));
		return;
	}

	MainGameWidget->AddToViewport();
	SetUIState(EUIState::InGame);
	UE_LOG(LogTemp, Log, TEXT("UIManager: Game UI shown"));
}

void UUIManager::HideGameUI()
{
	if (!MainGameWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIManager: MainGameWidget is null"));
		return;
	}

	MainGameWidget->RemoveFromParent();
	SetUIState(EUIState::Hidden);
	UE_LOG(LogTemp, Log, TEXT("UIManager: Game UI hidden"));
}

void UUIManager::SetUIState(EUIState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	EUIState OldState = CurrentState;
	CurrentState = NewState;

	BP_OnUIStateChanged(NewState);

	UE_LOG(LogTemp, Log, TEXT("UIManager: UI state changed from %d to %d"), 
		static_cast<int32>(OldState), static_cast<int32>(NewState));
}
