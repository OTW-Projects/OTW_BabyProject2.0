// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/GameTypes.h"
#include "VNSaveGame.generated.h"

UCLASS()
class OTW_BABYPROJECT_API UVNSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	FVNSaveData SaveData;
};
