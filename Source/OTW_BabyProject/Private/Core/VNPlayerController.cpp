// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VNPlayerController.h"
#include "Core/VNGameMode.h"
#include "Narrative/NarrativeManager.h"
#include "Blueprint/UserWidget.h"

AVNPlayerController::AVNPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AVNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode to UI only
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);

	// Create the main widget (but don't add to viewport yet - UIManager will handle that)
	if (WidgetClass)
	{
		MainWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (!MainWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("VNPlayerController: Failed to create main widget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VNPlayerController: No WidgetClass assigned"));
	}

	UE_LOG(LogTemp, Log, TEXT("VNPlayerController: Initialized"));
}

void AVNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		return;
	}

	// Bind input actions
	// Note: You'll need to set these up in Project Settings > Input
	InputComponent->BindAction("NextDialogue", IE_Pressed, this, &AVNPlayerController::OnNextDialogue);
	InputComponent->BindAction("SkipDialogue", IE_Pressed, this, &AVNPlayerController::OnSkipDialogue);
	InputComponent->BindAction("OpenMenu", IE_Pressed, this, &AVNPlayerController::OnOpenMenu);
}

void AVNPlayerController::OnNextDialogue()
{
	UNarrativeManager* NarrativeManager = GetNarrativeManager();
	if (NarrativeManager)
	{
		NarrativeManager->NextDialogue();
	}
}

void AVNPlayerController::OnSkipDialogue()
{
	// TODO: Implement skip logic
	UE_LOG(LogTemp, Log, TEXT("VNPlayerController: Skip dialogue requested"));
}

void AVNPlayerController::OnOpenMenu()
{
	// TODO: Implement menu opening
	UE_LOG(LogTemp, Log, TEXT("VNPlayerController: Open menu requested"));
}

UNarrativeManager* AVNPlayerController::GetNarrativeManager() const
{
	AVNGameMode* GameMode = Cast<AVNGameMode>(GetWorld()->GetAuthGameMode());
	return GameMode ? GameMode->GetNarrativeManager() : nullptr;
}