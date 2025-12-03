// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "OTW_BabyProject/Public/Types/GameTypes.h"
#include "GameFramework/GameModeBase.h"
#include "VNGameMode.generated.h"

class USaveManager;
class USceneDataAsset;
class UNarrativeManager;
class UUIManager;
class AVNPlayerController;
class AGameStateManager;

UCLASS()
class OTW_BABYPROJECT_API AVNGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AVNGameMode();

	//TEMPORARY -> Refactor later
	UPROPERTY(EditAnywhere, Category = "Starting Scene")
	TSoftObjectPtr<USceneDataAsset> StartingScene;
	
	UFUNCTION(BlueprintPure, Category = "Game Systems")
	UNarrativeManager* GetNarrativeManager() const { return NarrativeManager; }

	UFUNCTION(BlueprintPure, Category = "Game Systems")
	UUIManager* GetUIManager() const { return UIManager; }

	UFUNCTION(BlueprintPure, Category = "Game Systems")
	AGameStateManager* GetGameStateManager() const { return GameStateManager; }

	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool SaveGame(const FString& SlotName);
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool LoadGame(const FString& SlotName);
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool QuickSave();
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool QuickLoad();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UNarrativeManager> NarrativeManager;
	
	UPROPERTY()
	TObjectPtr<UUIManager> UIManager;

	UPROPERTY()
	TObjectPtr<AGameStateManager> GameStateManager;

	FVNSaveData GatherSaveData() const;

	void ApplySaveData(const FVNSaveData& SaveData);
    
	USaveManager* GetSaveManager() const;
	
	void InitializeGameSystems();
	void StartStory();

	// Event handlers - bridge between Narrative and UI
	UFUNCTION()
	void HandleDialogueChanged(const FDialogueLine& NewDialogueLine);
    
	UFUNCTION()
	void HandleSceneChanged(USceneDataAsset* NewScene);
};
