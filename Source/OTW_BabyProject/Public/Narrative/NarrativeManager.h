// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/GameTypes.h"
#include "NarrativeManager.generated.h"

class USceneDataAsset;

UCLASS(BlueprintType)
class OTW_BABYPROJECT_API UNarrativeManager : public UObject
{
	GENERATED_BODY()

public:
	// Events
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChanged, const FDialogueLine&, NewDialogueLine);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSceneChanged, USceneDataAsset*, NewScene);

	UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
	FOnDialogueChanged OnDialogueChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
	FOnSceneChanged OnSceneChanged;

	// Scene management
	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void LoadScene(USceneDataAsset* NewScene);

	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void LoadNextScene();

	// Dialogue progression
	UFUNCTION(BlueprintCallable, Category = "Narrative")
	void NextDialogue();

	// Getters
	UFUNCTION(BlueprintPure, Category = "Narrative")
	FDialogueLine GetCurrentDialogue() const;
    
	UFUNCTION(BlueprintPure, Category = "Narrative")
	USceneDataAsset* GetCurrentScene() const { return CurrentScene; }
    
	UFUNCTION(BlueprintPure, Category = "Narrative")
	int32 GetCurrentDialogueIndex() const { return CurrentDialogueIndex; }
    
	UFUNCTION(BlueprintPure, Category = "Narrative")
	bool IsSceneComplete() const;

private:
	void ResetDialogueIndex();
	
	UPROPERTY()
	TObjectPtr<USceneDataAsset> CurrentScene;

	int32 CurrentDialogueIndex;
};
