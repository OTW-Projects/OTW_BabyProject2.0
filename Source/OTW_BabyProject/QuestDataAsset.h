// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "QuestDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class OTW_BABYPROJECT_API UQuestDataAsset : public UGameData
{
	GENERATED_BODY()

public:

	static const FPrimaryAssetType QuestAssetType;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	EQuestState GetCurrentQuestState() const;
	void SetCurrentQuestState(EQuestState NewQuestState);
	
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
	EQuestState CurrentQuestState = EQuestState::Inactive;
};
