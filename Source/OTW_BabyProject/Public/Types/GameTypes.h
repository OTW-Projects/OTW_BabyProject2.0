#pragma once

#include "CoreMinimal.h"
#include "GameTypes.generated.h"

// Forward declarations
class USceneDataAsset;
class UCharacterDataAsset;

/**
 * Quest state enum
 */
UENUM(BlueprintType)
enum class EQuestState : uint8
{
	Inactive UMETA(DisplayName = "Inactive"),
	InProgress UMETA(DisplayName = "In Progress"),
	Completed UMETA(DisplayName = "Completed"),
	Abandoned UMETA(DisplayName = "Abandoned")
};

/**
 * UI state enum
 */
UENUM(BlueprintType)
enum class EUIState : uint8
{
	Hidden UMETA(DisplayName = "Hidden"),
	MainMenu UMETA(DisplayName = "Main Menu"),
	InGame UMETA(DisplayName = "In Game"),
	Paused UMETA(DisplayName = "Paused"),
	Loading UMETA(DisplayName = "Loading")
};

/**
 * Single line of dialogue
 */
USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (MultiLine = true))
	FString DialogueText;

	// Optional: Character data for more complex systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSoftObjectPtr<UCharacterDataAsset> Speaker;

	FDialogueLine()
		: SpeakerName(TEXT(""))
		, DialogueText(TEXT(""))
	{}
};
