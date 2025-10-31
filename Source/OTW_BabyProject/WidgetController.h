// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OTW_BabyProject/SceneDataAsset.h"
#include "OTW_BabyProject/NarrativeManager.h"
#include "OTW_BabyProject/UIManager.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"


UCLASS(BLueprintable, BlueprintType)
class OTW_BABYPROJECT_API UWidgetController : public UObject
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<UNarrativeManager> NarrativeManager;

	UPROPERTY()
	TObjectPtr<UUIManager> UIManager;

public:
	
	UFUNCTION(BlueprintCallable)
	void Init(UNarrativeManager* InNarrativeManager, UUIManager* InUIManager);
	
	UFUNCTION(BlueprintCallable)
	void HandleDialogueChanged(const FDialogueLine& NewLine);

	UFUNCTION(BlueprintCallable)
	void HandleSceneChanged(const USceneDataAsset* NewScene);

	UFUNCTION(BlueprintCallable)
	void OnNextButtonPressed();

	UFUNCTION(BlueprintCallable)
	void ShowGameUI();

	UFUNCTION(BlueprintCallable)
	void HideGameUI();
};
