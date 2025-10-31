// Fill out your copyright notice in the Description page of Project Settings.


#include "VNGameMode.h"

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

	StartStory();
	
	NarrativeManager->Initialize();

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
