// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/NoExportTypes.h"
#include "OTW_BabyProject/Public/Types/GameTypes.h"
#include "UIManager.generated.h"

class APlayerController;


UCLASS(Blueprintable, BlueprintType)
class OTW_BABYPROJECT_API UUIManager : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> MainGameWidget;
	
	UPROPERTY()
	EUIState CurrentState = EUIState::Hidden;
	
public:

	UFUNCTION(BlueprintCallable)
	void Initialize(TSubclassOf<UUserWidget> InWidgetClass, APlayerController* OwnerController);

	UFUNCTION(BlueprintCallable)
	void ShowDialogueUI(const FString& SpeakerName, const FString& DialogueText);

	UFUNCTION(BlueprintCallable)
	void SetBackground(const FSoftObjectPath& BackgroundImagePath);

	UFUNCTION(BlueprintCallable)
	void ShowGameUI();

	UFUNCTION(BlueprintCallable)
	void HideGameUI();

	UFUNCTION(BlueprintCallable)
	void SetUIState(EUIState NewState);
	
	UFUNCTION(BlueprintCallable)
	void ShowSceneTransitionUI();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnDialogueChanged(const FString& Speaker, const FString& Text);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnBackgroundChanged(const FSoftObjectPath& BackgroundImagePath);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnUIStateChanged(EUIState NewState);

private:

	void CreateMainGameWidget(TSubclassOf<UUserWidget> WidgetClass, APlayerController* OwnerController);

	void UpdateDialogueWidget(const FString& Speaker, const FString& Text);

	void UpdateBackgroundWidget(const FSoftObjectPath& BackgroundPath);
};
