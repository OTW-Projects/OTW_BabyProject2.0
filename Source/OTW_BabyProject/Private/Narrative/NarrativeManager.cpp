// Fill out your copyright notice in the Description page of Project Settings.


#include "Narrative/NarrativeManager.h"
#include "Data/SceneDataAsset.h"

void UNarrativeManager::LoadScene(USceneDataAsset* NewScene)
{
	if (!NewScene)
	{
		UE_LOG(LogTemp, Warning, TEXT("NarrativeManager: Attempted to load null scene"));
		return;
	}

	if (NewScene->DialogueLines.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NarrativeManager: Scene '%s' has no dialogue lines"), *NewScene->GetName());
		return;
	}

	CurrentScene = NewScene;
	ResetDialogueIndex();

	// Broadcast events
	OnSceneChanged.Broadcast(CurrentScene);
	OnDialogueChanged.Broadcast(GetCurrentDialogue());

	UE_LOG(LogTemp, Log, TEXT("NarrativeManager: Loaded scene '%s' with %d dialogue lines"), 
		*NewScene->GetName(), NewScene->DialogueLines.Num());
}

void UNarrativeManager::LoadNextScene()
{
	if (!CurrentScene)
	{
		UE_LOG(LogTemp, Warning, TEXT("NarrativeManager: No current scene to transition from"));
		return;
	}

	if (!CurrentScene->NextScene)
	{
		UE_LOG(LogTemp, Log, TEXT("NarrativeManager: Reached end of story"));
		return;
	}

	LoadScene(CurrentScene->NextScene);
}

void UNarrativeManager::NextDialogue()
{
	if (!CurrentScene)
	{
		UE_LOG(LogTemp, Warning, TEXT("NarrativeManager: No scene loaded"));
		return;
	}

	if (CurrentScene->DialogueLines.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NarrativeManager: Current scene has no dialogues"));
		return;
	}
    
	// Check if we're at the last dialogue
	if (IsSceneComplete())
	{
		UE_LOG(LogTemp, Log, TEXT("NarrativeManager: Scene complete, loading next scene"));
		LoadNextScene();
		return;
	}
	
	// Advance dialogue
	CurrentDialogueIndex++;
	OnDialogueChanged.Broadcast(GetCurrentDialogue());

	UE_LOG(LogTemp, Log, TEXT("NarrativeManager: Advanced to dialogue %d/%d"), 
		CurrentDialogueIndex + 1, CurrentScene->DialogueLines.Num());
}

FDialogueLine UNarrativeManager::GetCurrentDialogue() const
{
	if (!CurrentScene || CurrentDialogueIndex < 0 || 
		CurrentDialogueIndex >= CurrentScene->DialogueLines.Num())
	{
		return FDialogueLine();
	}
    
	return CurrentScene->DialogueLines[CurrentDialogueIndex];
}

bool UNarrativeManager::IsSceneComplete() const
{
	if (!CurrentScene)
	{
		return true;
	}

	return CurrentDialogueIndex >= CurrentScene->DialogueLines.Num() - 1;
}

void UNarrativeManager::ResetDialogueIndex()
{
	CurrentDialogueIndex = 0;
}