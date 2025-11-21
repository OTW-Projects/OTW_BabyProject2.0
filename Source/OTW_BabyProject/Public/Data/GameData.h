// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OTW_BabyProject/Public/Types/GameTypes.h"
#include "GameData.generated.h"

UCLASS(Abstract, BlueprintType)
class OTW_BABYPROJECT_API UGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data", meta=(AllowPrivateAccess="true"))
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data", meta=(AllowPrivateAccess="true"))
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data", meta=(AllowPrivateAccess="true"))
	TArray<FName> Tags;
};
