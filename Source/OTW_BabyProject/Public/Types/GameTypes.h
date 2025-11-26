// © 2025 Open To Work - Samuel Abel

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

UENUM(BlueprintType)
enum class EConsequenceType : uint8
{
	ModifyStat UMETA(DisplayName = "Modify Stat"),
	SetFlag UMETA(DisplayName = "Set Flag"),
	ModifyRelationship UMETA(DisplayName = "Modify Relationship"),
	GiveItem UMETA(DisplayName = "Give Item"),
	RemoveItem UMETA(DisplayName = "Remove Item"),
	UnlockScene UMETA(DisplayName = "Unlock Scene"),
	CustomEvent UMETA(DisplayName = "Custom Event")
};

UENUM(BlueprintType)
enum class EOperation : uint8
{
	Set UMETA(DisplayName = "Set"),
	Add UMETA(DisplayName = "Add"),
	Subtract UMETA(DisplayName = "Subtract"),
	Multiply UMETA(DisplayName = "Multiply")
};

/**
 * Single line of dialogue
 */
USTRUCT(BlueprintType)
struct FChoiceConsequence
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConsequenceType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Target; // "JohnRelationship", "HasKey", etc.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperation Operation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	FChoiceConsequence()
		: Type(EConsequenceType::ModifyStat)
		, Target(NAME_None)
		, Operation(EOperation::Add)
		, Value(0.0f)
	{}
};

USTRUCT(BlueprintType)
struct FChoiceOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ChoiceText; // "Help the stranger"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USceneDataAsset> NextScene; // Optional: jump to new scene

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextDialogueIndex; // Optional: jump within same scene (-1 = continue normally)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChoiceConsequence> Consequences; // What happens if chosen

	// Future: requirements to show/enable this choice
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// TArray<FChoiceRequirement> Requirements;

	FChoiceOption()
		: ChoiceText(TEXT(""))
		, NextScene(nullptr)
		, NextDialogueIndex(-1)
	{}
};

USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (MultiLine = true))
	FString DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSoftObjectPtr<UCharacterDataAsset> Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bHasChoice"))
	TArray<FChoiceOption> Choices;

	FDialogueLine()
		: SpeakerName(TEXT(""))
		, DialogueText(TEXT(""))
		, bHasChoice(false)
	{}
};