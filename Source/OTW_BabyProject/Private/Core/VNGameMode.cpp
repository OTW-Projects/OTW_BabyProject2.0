// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VNGameMode.h"

#include "Core/NarrativeGameInstance.h"

AVNGameMode::AVNGameMode()
{
	DefaultPawnClass = nullptr;

	PlayerControllerClass = AVNPlayerController::StaticClass();
}

void AVNGameMode::BeginPlay()
{
	Super::BeginPlay();

	UNarrativeGameInstance* GameInstance = Cast<UNarrativeGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		InitializeGameSystems();
	}
}

void AVNGameMode::InitializeGameSystems()
{
	NarrativeManager = NewObject<UNarrativeManager>(this, UNarrativeManager::StaticClass());
	if (!NarrativeManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create NarrativeManager"));
		return;
	}

	UIManager = NewObject<UUIManager>(this, UUIManager::StaticClass());
	if (!UIManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create UIManager"));
		return;
	}

	AVNPlayerController* PlayerController = Cast<AVNPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get VNPlayerController"));
		return;
	}

	UIManager->Initialize(PlayerController->WidgetClass, PlayerController);

	// ✅ BIND THE EVENTS - This connects NarrativeManager to UIManager!
	NarrativeManager->OnDialogueChanged.AddDynamic(this, &AVNGameMode::HandleDialogueChanged);
	NarrativeManager->OnSceneChanged.AddDynamic(this, &AVNGameMode::HandleSceneChanged);

	StartStory();

	UE_LOG(LogTemp, Log, TEXT("Game systems initialized successfully"));
}

void AVNGameMode::StartStory()
{
	if (!StartingScene.IsNull())
	{
		USceneDataAsset* FirstScene = StartingScene.LoadSynchronous();
		if (FirstScene)
		{
			NarrativeManager->LoadScene(FirstScene);

			UIManager->ShowGameUI();

			UE_LOG(LogTemp, Log, TEXT("Story started with scene: %s"), *FirstScene->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load starting scene"));
		}
	}
}

void AVNGameMode::HandleDialogueChanged(const FDialogueLine& NewDialogueLine)
{
	if (UIManager)
	{
		UIManager->ShowDialogueUI(NewDialogueLine.SpeakerName, NewDialogueLine.DialogueText);
	}
}

void AVNGameMode::HandleSceneChanged(USceneDataAsset* NewScene)
{
	if (UIManager && NewScene)
	{
		UIManager->SetBackground(NewScene->BackgroundImage);
		UE_LOG(LogTemp, Log, TEXT("Scene changed to: %s"), *NewScene->GetName());
	}
}
