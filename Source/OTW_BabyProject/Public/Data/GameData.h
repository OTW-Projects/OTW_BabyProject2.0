// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData.generated.h"

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	Inactive UMETA(DisplayName = "Inactive"),
	InProgress UMETA(DisplayName = "InProgress"),
	Completed UMETA(DisplayName = "Completed"),
	Abandoned UMETA(DisplayName = "Abandoned"),
};

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
