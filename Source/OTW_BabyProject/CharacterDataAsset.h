// Fill out your copyright notice in the Description page of Project Settings.

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
};
