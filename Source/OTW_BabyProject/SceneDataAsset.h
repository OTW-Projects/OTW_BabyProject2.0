// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "SceneDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SpeakerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DialogueText;
};


UCLASS()
class OTW_BABYPROJECT_API USceneDataAsset : public UGameData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	FSoftObjectPath BackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	TArray<FDialogueLine> DialogueLines;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	USceneDataAsset* NextScene;
};
