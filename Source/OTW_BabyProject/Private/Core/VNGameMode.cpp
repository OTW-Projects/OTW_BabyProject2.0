// © 2025 Open To Work - Samuel Abel

#include "Core/VNGameMode.h"

#include "Core/SaveManager.h"
#include "Core/VNPlayerController.h"
#include "Data/SceneDataAsset.h"
#include "Narrative/NarrativeManager.h"
#include "UI/UIManager.h"

AVNGameMode::AVNGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AVNPlayerController::StaticClass();
	GameStateManager = Cast<AGameStateManager>(GameStateClass);
}

void AVNGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeGameSystems();
}

bool AVNGameMode::SaveGame(const FString& SlotName)
{
	USaveManager* SaveManager = GetSaveManager();
	if (!SaveManager)
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode : SaveManager not found"));
		return false;
	}

	FVNSaveData SaveData = GatherSaveData();
	SaveData.SaveSlotName = SlotName;
	SaveData.SaveDateTime = FDateTime::Now();

	bool bSuccess = SaveManager->SaveGameToSlot(SaveData, SlotName);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("VNGameMode : Game saved to slot: %s"), *SlotName);
	}

	return bSuccess;
}

bool AVNGameMode::LoadGame(const FString& SlotName)
{
	return true;
}

bool AVNGameMode::QuickSave()
{
	return true;
}

bool AVNGameMode::QuickLoad()
{
	return true;
}


FVNSaveData AVNGameMode::GatherSaveData() const
{
	FVNSaveData SaveData;

	if (NarrativeManager)
	{
		if (USceneDataAsset* CurrentScene = NarrativeManager->GetCurrentScene())
		{
			SaveData.CurrentSceneId = CurrentScene->GetName();
		}
		SaveData.CurrentDialogueIndex = NarrativeManager->GetCurrentDialogueIndex();
	}

	if (GameStateManager)
	{
		SaveData.Flags = GameStateManager->GetAllFlags();
		SaveData.Stats = GameStateManager->GetAllStats();
		SaveData.Relationships = GameStateManager->GetAllRelationships();
	}

	return SaveData;
}

void AVNGameMode::ApplySaveData(const FVNSaveData& SaveData)
{
	
}

USaveManager* AVNGameMode::GetSaveManager() const
{
	return Cast<USaveManager>(GetSaveManager());
}

void AVNGameMode::InitializeGameSystems()
{
	// Create managers
	NarrativeManager = NewObject<UNarrativeManager>(this);
	if (!NarrativeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode: Failed to create NarrativeManager"));
		return;
	}

	UIManager = NewObject<UUIManager>(this);
	if (!UIManager)
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode: Failed to create UIManager"));
		return;
	}

	// Get player controller
	AVNPlayerController* PlayerController = Cast<AVNPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode: Failed to get VNPlayerController"));
		return;
	}

	// Initialize UI
	UIManager->Initialize(PlayerController->GetWidgetClass(), PlayerController);

	// Bind narrative events to UI updates
	NarrativeManager->OnDialogueChanged.AddDynamic(this, &AVNGameMode::HandleDialogueChanged);
	NarrativeManager->OnSceneChanged.AddDynamic(this, &AVNGameMode::HandleSceneChanged);

	// Start the story
	StartStory();

	UE_LOG(LogTemp, Log, TEXT("VNGameMode: All game systems initialized successfully"));
}

void AVNGameMode::StartStory()
{
	if (StartingScene.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode: No starting scene assigned"));
		return;
	}

	USceneDataAsset* FirstScene = StartingScene.LoadSynchronous();
	if (!FirstScene)
	{
		UE_LOG(LogTemp, Error, TEXT("VNGameMode: Failed to load starting scene"));
		return;
	}

	NarrativeManager->LoadScene(FirstScene);
	UIManager->ShowGameUI();

	UE_LOG(LogTemp, Log, TEXT("VNGameMode: Story started with scene '%s'"), *FirstScene->GetName());
}

void AVNGameMode::HandleDialogueChanged(const FDialogueLine& NewDialogueLine)
{
	if (UIManager)
	{
		UIManager->UpdateDialogue(NewDialogueLine.SpeakerName, NewDialogueLine.DialogueText);
	}
}

void AVNGameMode::HandleSceneChanged(USceneDataAsset* NewScene)
{
	if (!UIManager || !NewScene)
	{
		return;
	}

	UIManager->UpdateBackground(NewScene->BackgroundImage);
	UE_LOG(LogTemp, Log, TEXT("VNGameMode: Scene changed to '%s'"), *NewScene->GetName());
}

