// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Types/GameTypes.h"
#include "GameStateManager.generated.h"



UCLASS()
class OTW_BABYPROJECT_API AGameStateManager : public AGameStateBase
{
	GENERATED_BODY()
	
	TMap<FName, bool> Flags;
	TMap<FName, float> Stats;
	TMap<FName, float> Relationships;

public:

	// GETTERS
	bool GetFlag(FName FlagName) const;
	float GetStat(FName StatName) const;
	float GetRelationship(FName CharacterName) const;

	//SETTERS
	void SetFlag(FName FlagName, bool Value);
	void SetStat(FName StatName, float Value);
	void SetRelationship(FName CharacterName, float Value);

	//MODIFIERS
	void ModifyStat(FName StatName, float Delta);
	void ModifyRelationship(FName CharacterName, float Delta);

	//CONSEQUENCES
	UFUNCTION(BlueprintCallable)
	void ApplyConsequence(const FChoiceConsequence& Consequence);

	//TOOLS
	UFUNCTION(BlueprintCallable)
	bool HasStat(FName StatName) const;
};
