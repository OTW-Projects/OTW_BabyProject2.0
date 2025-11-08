// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OTW_BabyProject/Public/Data/SceneDataAsset.h"
#include "OTW_BabyProject/Public/Narrative/NarrativeManager.h"
#include "OTW_BabyProject/Public/UI/UIManager.h"
#include "OTW_BabyProject/Public/Core/VNPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "VNGameMode.generated.h"

UCLASS()
class OTW_BABYPROJECT_API AVNGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AVNGameMode();

	//TEMPORARY -> Refactor later
	UPROPERTY(EditAnywhere, Category = "Starting Scene")
	TSoftObjectPtr<USceneDataAsset> StartingScene;
	
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UNarrativeManager> NarrativeManager;
	
	UPROPERTY()
	TObjectPtr<UUIManager> UIManager;

	void InitializeGameSystems();

	void StartStory();

	UFUNCTION()
	void HandleDialogueChanged(const FDialogueLine& NewDialogueLine);
    
	UFUNCTION()
	void HandleSceneChanged(USceneDataAsset* NewScene);
};
