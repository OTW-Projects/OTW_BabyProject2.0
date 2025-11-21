// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "SceneDataAsset.generated.h"


UCLASS()
class OTW_BABYPROJECT_API USceneDataAsset : public UGameData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Scene")
	FName SceneID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	FSoftObjectPath BackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	TArray<FDialogueLine> DialogueLines;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Scene")
	USceneDataAsset* NextScene;
};
