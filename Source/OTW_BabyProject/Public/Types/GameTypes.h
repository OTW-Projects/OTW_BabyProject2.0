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

USTRUCT(BlueprintType)
struct FVNSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FDateTime SaveDateTime;
    
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotName;
	
	UPROPERTY(BlueprintReadWrite)
	FString CurrentSceneId;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentDialogueIndex;

	UPROPERTY(BlueprintReadWrite)
	TMap<FName, bool> Flags;
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FName, float> Stats;
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FName, float> Relationships;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> ChoiceHistory;

	FVNSaveData()
		: SaveDateTime(FDateTime::Now())
		, SaveSlotName(TEXT(""))
		, CurrentSceneId(TEXT(""))
		, CurrentDialogueIndex(0)
	{}
};

USTRUCT(BLueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Awareness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stress;
};


USTRUCT(BlueprintType)
struct FChoiceConsequence
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConsequenceType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Target; 

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
	FString ChoiceText; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USceneDataAsset> NextScene; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextDialogueIndex; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChoiceConsequence> Consequences;

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