// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NarrativeGameInstance.generated.h"


UCLASS(Blueprintable, BlueprintType)
class OTW_BABYPROJECT_API UNarrativeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	// TODO: Add save/load functionality here
	
	// TODO: Add persistent game settings here
};
