// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/NarrativeManager.h"

void UNarrativeManager::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("NarrativeManager initialized"));
}

UNarrativeManager::UNarrativeManager() : CurrentScene(nullptr), CurrentDialogueIndex(0)
{
}

void UNarrativeManager::NextDialogue()
{
	if (!CurrentScene || CurrentScene->DialogueLines.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No scene or dialogues available"));
		return;
	}
    
	// Check if we're at the last dialogue BEFORE incrementing
	if (CurrentDialogueIndex >= CurrentScene->DialogueLines.Num() - 1)
	{
		UE_LOG(LogTemp, Log, TEXT("Scene complete, loading next scene"));
		LoadNextScene();
		return;
	}
	
	CurrentDialogueIndex++;
	CurrentDialogue = CurrentScene->DialogueLines[CurrentDialogueIndex];

	if (OnDialogueChanged.IsBound())
	{
		OnDialogueChanged.Broadcast(CurrentScene->DialogueLines[CurrentDialogueIndex]);
	}

	UE_LOG(LogTemp, Log, TEXT("Advanced to dialogue %d"), CurrentDialogueIndex);
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
	if (NewScene != nullptr && NewScene->DialogueLines.Num() > 0)
	{
		CurrentScene = NewScene;
		ResetDialogueCount();

		CurrentDialogue = CurrentScene->DialogueLines[CurrentDialogueIndex];
		
		if (OnSceneChanged.IsBound())
		{
			OnSceneChanged.Broadcast(CurrentScene->NextScene);
		}

		if (OnDialogueChanged.IsBound())
		{
			OnDialogueChanged.Broadcast(CurrentDialogue);
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded scene: %s with %d dialogue lines"), *NewScene->GetName(), NewScene->DialogueLines.Num());
	}
}

void UNarrativeManager::LoadNextScene()
{
	LoadScene(CurrentScene->NextScene);
}