// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OTW_BabyProject/SceneDataAsset.h"
#include "NarrativeManager.generated.h"


UCLASS(BlueprintType)
class OTW_BABYPROJECT_API UNarrativeManager : public UObject
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChanged, const FDialogueLine&, NewDialogueLine);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSceneChanged, USceneDataAsset*, NewScene);

	UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
	FOnDialogueChanged OnDialogueChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
	FOnSceneChanged OnSceneChanged;
	
	void Initialize();

	UNarrativeManager();
	
	UFUNCTION(BlueprintCallable)
	void LoadScene(USceneDataAsset* NewScene);

	UFUNCTION(BlueprintCallable)
	void LoadNextScene();

	UFUNCTION(BlueprintCallable)
	void NextDialogue();

	// Getters
	UFUNCTION(BlueprintCallable)
	FDialogueLine GetCurrentDialogue() const;
    
	UFUNCTION(BlueprintCallable)
	USceneDataAsset* GetCurrentScene() const { return CurrentScene; }
    
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentDialogueIndex() const { return CurrentDialogueIndex; }
    
	UFUNCTION(BlueprintCallable)
	bool IsSceneComplete() const;

private:

	void ResetDialogueCount();
	
	int32 CurrentDialogueIndex = 0;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USceneDataAsset* CurrentScene;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FDialogueLine CurrentDialogue;
};
