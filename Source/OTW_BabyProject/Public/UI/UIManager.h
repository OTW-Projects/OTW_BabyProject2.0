// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OTW_BabyProject/Public/Types/GameTypes.h"
#include "UIManager.generated.h"

class UUserWidget;
class APlayerController;

UCLASS(Blueprintable, BlueprintType)
class OTW_BABYPROJECT_API UUIManager : public UObject
{
	GENERATED_BODY()

public:
	// Initialization
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Initialize(TSubclassOf<UUserWidget> InWidgetClass, APlayerController* OwnerController);

	// UI updates (called by GameMode in response to narrative events)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateDialogue(const FString& SpeakerName, const FString& DialogueText);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateBackground(const FSoftObjectPath& BackgroundImagePath);

	// UI visibility
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowGameUI();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideGameUI();

	// UI state management
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetUIState(EUIState NewState);

	UFUNCTION(BlueprintPure, Category = "UI")
	EUIState GetUIState() const { return CurrentState; }

	// Blueprint implementable events for custom UI logic
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void BP_OnDialogueChanged(const FString& Speaker, const FString& Text);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void BP_OnBackgroundChanged(const FSoftObjectPath& BackgroundImagePath);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void BP_OnUIStateChanged(EUIState NewState);

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainGameWidget;
	
	UPROPERTY()
	EUIState CurrentState;
};
