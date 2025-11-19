// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VNGameMode.h"
#include "Core/VNPlayerController.h"
#include "Data/SceneDataAsset.h"
#include "Narrative/NarrativeManager.h"
#include "UI/UIManager.h"

AVNGameMode::AVNGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AVNPlayerController::StaticClass();
}

void AVNGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeGameSystems();
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

