// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OTW_BabyProject/Public/Types/GameTypes.h"
#include "UIManager.generated.h"

class UUserWidget;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueUpdateSignature, const FString&, Speaker, const FString&, Text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBackgroundUpdateSignature, const FSoftObjectPath&, BackgroundPath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIStateChangedSignature, EUIState, NewState);

UCLASS()
class OTW_BABYPROJECT_API UUIManager : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FOnDialogueUpdateSignature OnDialogueUpdate;
	
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FOnBackgroundUpdateSignature OnBackgroundUpdate;
	
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FOnUIStateChangedSignature OnUIStateChanged;
	
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

	UFUNCTION(BlueprintPure, Category = "UI")
	UUserWidget* GetMainWidget() const { return MainGameWidget; }
	
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainGameWidget;
	
	UPROPERTY()
	EUIState CurrentState;
};
