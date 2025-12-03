// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class OTW_BABYPROJECT_API USaveManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Core save/load operations
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool SaveGameToSlot(const FVNSaveData& SaveData, const FString& SlotName);
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool LoadGameFromSlot(const FString& SlotName, FVNSaveData& OutSaveData);
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool DeleteSaveSlot(const FString& SlotName);
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	bool DoesSaveExist(const FString& SlotName) const;
    
	// Utility
	UFUNCTION(BlueprintCallable, Category = "Save System")
	TArray<FString> GetAllSaveSlots() const;
    
	UFUNCTION(BlueprintCallable, Category = "Save System")
	FVNSaveData GetSaveMetadata(const FString& SlotName) const;

private:
	// Helper to get standardized save file names
	FString GetSaveSlotFileName(const FString& SlotName) const;
};
