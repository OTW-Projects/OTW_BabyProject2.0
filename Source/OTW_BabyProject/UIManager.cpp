// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

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
	
	CreateMainGameWidget(InWidgetClass, OwnerController);
	
	UE_LOG(LogTemp, Log, TEXT("UIManager initialized successfully"));
}

void UUIManager::ShowDialogueUI(const FString& SpeakerName, const FString& DialogueText)
{
	if (CurrentState != EUIState::InGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIManager: Trying to show dialogue while not in game state"));
		return;
	}

	UpdateDialogueWidget(SpeakerName, DialogueText);

	BP_OnDialogueChanged(SpeakerName, DialogueText);

	UE_LOG(LogTemp, Log, TEXT("Showing dialogue - %s: %s"), *SpeakerName, *DialogueText);
}

void UUIManager::SetBackground(const FSoftObjectPath& BackgroundImagePath)
{
	UpdateBackgroundWidget(BackgroundImagePath);

	BP_OnBackgroundChanged(BackgroundImagePath);

	UE_LOG(LogTemp, Log, TEXT("Setting background - %s"), *BackgroundImagePath.ToString());
}

void UUIManager::ShowGameUI()
{
	if (MainGameWidget)
	{
		MainGameWidget->AddToViewport();
		SetUIState(EUIState::InGame);
		UE_LOG(LogTemp, Log, TEXT("Game UI shown"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: MainGameWidget is null, cannot show game UI"));
	}
}

void UUIManager::HideGameUI()
{
	if (MainGameWidget)
	{
		MainGameWidget->RemoveFromParent();
		SetUIState(EUIState::Hidden);
		UE_LOG(LogTemp, Log, TEXT("Game UI hidden"));
	}
}

void UUIManager::SetUIState(EUIState NewState)
{
	if (CurrentState != NewState)
	{
		EUIState OldState = CurrentState;
		CurrentState = NewState;

		BP_OnUIStateChanged(NewState);

		UE_LOG(LogTemp, Log, TEXT("UI state changed from %d to %d"), (int32)OldState, (int32)NewState);
	}
}

void UUIManager::ShowSceneTransitionUI()
{
}

void UUIManager::CreateMainGameWidget(TSubclassOf<UUserWidget> WidgetClass, APlayerController* OwnerController)
{
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: WidgetClass is null, cannot create main game widget"));
		return;
	}

	MainGameWidget = CreateWidget<UUserWidget>(OwnerController, WidgetClass);
    
	if (MainGameWidget)
	{
		MainGameWidget->AddToViewport();
		SetUIState(EUIState::InGame);
		UE_LOG(LogTemp, Log, TEXT("Main game widget created and added to viewport"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager: Failed to create main game widget"));
	}
}

void UUIManager::UpdateDialogueWidget(const FString& Speaker, const FString& Text)
{
	UE_LOG(LogTemp, Log, TEXT("UpdateDialogueWidget: %s says '%s'"), *Speaker, *Text);
}

void UUIManager::UpdateBackgroundWidget(const FSoftObjectPath& BackgroundPath)
{
	
}