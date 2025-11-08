// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController.h"

void UWidgetController::Init(UNarrativeManager* InNarrativeManager, UUIManager* InUIManager)
{
	if (!InNarrativeManager || !InUIManager)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetController: Invalid managers passed to Initialize"));
		return;
	}

	NarrativeManager = InNarrativeManager;
	UIManager = InUIManager;

	/*NarrativeManager->OnDialogueChanged.AddUObject(this, &UWidgetController::HandleDialogueChanged);
	NarrativeManager->OnSceneChanged.AddUObject(this, &UWidgetController::HandleSceneChanged);*/

	UE_LOG(LogTemp, Log, TEXT("WidgetController initialized successfully"));
}

void UWidgetController::HandleDialogueChanged(const FDialogueLine& NewLine)
{
	if (UIManager)
	{
		UIManager->ShowDialogueUI(NewLine.SpeakerName, NewLine.DialogueText);
	}
}

void UWidgetController::HandleSceneChanged(const USceneDataAsset* NewScene)
{
	if (!NewScene)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetController: New scene is NULL"));
		return;
	}

	if (UIManager)
	{
		UIManager->SetBackground(NewScene->BackgroundImage);
	}
}

void UWidgetController::OnNextButtonPressed()
{
	if (NarrativeManager)
	{
		NarrativeManager->NextDialogue();
	}
}

void UWidgetController::ShowGameUI()
{
	if (UIManager)
	{
		UIManager->ShowGameUI();

		if (NarrativeManager)
		{
		}
	}
}

void UWidgetController::HideGameUI()
{
	if (UIManager)
	{
		UIManager->HideGameUI();
	}
}