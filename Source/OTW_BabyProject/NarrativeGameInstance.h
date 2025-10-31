// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NarrativeManager.h"
#include "NarrativeGameInstance.generated.h"


UCLASS(BLueprintable, BlueprintType)
class OTW_BABYPROJECT_API UNarrativeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	UNarrativeManager* GetNarrativeManager() const { return NarrativeManager; }

private:

	UPROPERTY()
	UNarrativeManager* NarrativeManager;
};
