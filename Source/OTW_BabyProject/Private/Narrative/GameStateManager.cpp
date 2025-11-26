// © 2025 Open To Work - Samuel Abel

#include "Narrative/GameStateManager.h"

bool AGameStateManager::GetFlag(FName FlagName) const
{
	return Flags[FlagName];
}

float AGameStateManager::GetStat(FName StatName) const
{
	return Stats[StatName];
}

float AGameStateManager::GetRelationship(FName CharacterName) const
{
	return Relationships[CharacterName];
}

void AGameStateManager::SetFlag(FName FlagName, bool Value)
{
	Flags[FlagName] = Value;
}

void AGameStateManager::SetStat(FName StatName, float Value)
{
	if (!Value || Value < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameStateManager: Trying to set stat with an invalid Value parameter."));
		return;
	}
	Stats[StatName] = Value;
}

void AGameStateManager::SetRelationship(FName CharacterName, float Value)
{
	if (!Value || Value < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameStateManager: Trying to set relationship with an invalid Value parameter."));
		return;
	}
	Relationships[CharacterName] = Value;
}

void AGameStateManager::ModifyStat(FName StatName, float Delta)
{
    if (!Delta || Delta < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameStateManager: Trying to modify stat with an invalid Delta parameter."));
		return;
	}
	Stats[StatName] += Delta;
}

void AGameStateManager::ModifyRelationship(FName CharacterName, float Delta)
{
    if (!Delta || Delta < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameStateManager: Trying to modify relationship with an invalid Delta parameter."));
		return;
	}
	Relationships[CharacterName] += Delta;
}

void AGameStateManager::ApplyConsequence(const FChoiceConsequence& Consequence)
{
	const EOperation CurrentOperation = Consequence.Operation;

	switch (Consequence.Type)
	{
	case EConsequenceType::SetFlag:
		SetFlag(Consequence.Target, bool(Consequence.Value));
		break;

	case EConsequenceType::ModifyStat:
		if (CurrentOperation == EOperation::Set)
		{
			SetStat(Consequence.Target, Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Add)
		{
			ModifyStat(Consequence.Target, Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Subtract)
		{
			ModifyStat(Consequence.Target, -Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Multiply)
		{
			float newValue = GetStat(Consequence.Target) * Consequence.Value;
			SetStat(Consequence.Target, newValue);
		}
		break;

	case EConsequenceType::ModifyRelationship:
		if (CurrentOperation == EOperation::Set)
		{
			SetRelationship(Consequence.Target, Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Add)
		{
			ModifyRelationship(Consequence.Target, Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Subtract)
		{
			ModifyRelationship(Consequence.Target, -Consequence.Value);
		}
		else if (CurrentOperation == EOperation::Multiply)
		{
			float newValue = GetRelationship(Consequence.Target) * Consequence.Value;
			SetRelationship(Consequence.Target, newValue);
		}
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("GameStateManager: Type of consequence is invalid."));
	}
}

bool AGameStateManager::HasStat(FName StatName) const
{
	return Stats.Contains(StatName);
}
