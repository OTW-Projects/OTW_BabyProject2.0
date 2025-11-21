// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OTW_BABYPROJECT_API UCharacterDataAsset : public UGameData
{
	GENERATED_BODY()

public:

	static const FPrimaryAssetType CharacterAssetType;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character")
	FSoftObjectPath CharacterAsset;
};
