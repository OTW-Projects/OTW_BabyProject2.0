// Fill out your copyright notice in the Description page of Project Settings.


#include "NarrativeManager.h"

void UNarrativeManager::Initialize()
{
	if (CurrentScene)
	{
		CurrentDialogue = CurrentScene->DialogueLines[CurrentDialogueIndex];
	}
}

UNarrativeManager::UNarrativeManager() : CurrentScene(nullptr), CurrentDialogueIndex(0)
{
}

void UNarrativeManager::NextDialogue()
{
	CurrentDialogueIndex++;

	if (OnDialogueChanged.IsBound())
	{
		OnDialogueChanged.Broadcast(CurrentScene->DialogueLines[CurrentDialogueIndex]);
	}
	
	if (CurrentDialogueIndex >= CurrentScene->DialogueLines.Num())
	{
		LoadNextScene();
		ResetDialogueCount();
	}

}

FDialogueLine UNarrativeManager::GetCurrentDialogue() const
{
	if (CurrentScene && CurrentDialogueIndex >= 0 && 
	   CurrentDialogueIndex < CurrentScene->DialogueLines.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("Current Dialogue Index: %d"), CurrentDialogueIndex);
		return CurrentScene->DialogueLines[CurrentDialogueIndex];
	}
    
	// Return empty dialogue if invalid
	return FDialogueLine();
}

bool UNarrativeManager::IsSceneComplete() const
{
	if (!CurrentScene) return true;

	return CurrentDialogueIndex >= CurrentScene->DialogueLines.Num() - 1;
}

void UNarrativeManager::ResetDialogueCount()
{
	CurrentDialogueIndex = 0;
}

void UNarrativeManager::LoadScene(USceneDataAsset* NewScene)
{
	if (NewScene != nullptr)
	{
		CurrentScene = NewScene;
		ResetDialogueCount();

		if (OnSceneChanged.IsBound())
		{
			OnSceneChanged.Broadcast(CurrentScene->NextScene);
		}
	}
}

void UNarrativeManager::LoadNextScene()
{
	LoadScene(CurrentScene->NextScene);
}