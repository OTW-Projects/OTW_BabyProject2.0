// Fill out your copyright notice in the Description page of Project Settings.


#include "VNPlayerController.h"

AVNPlayerController::AVNPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	CurrentWidget = nullptr;
}

void AVNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);

	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	UE_LOG(LogTemp, Log, TEXT("VNPlayerController initialized"));
}

void AVNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AVNPlayerController::OnNextDialogue()
{
	UE_LOG(LogTemp, Log, TEXT("Next dialogue input received"));
}

void AVNPlayerController::OnSkipDialogue()
{
	UE_LOG(LogTemp, Log, TEXT("Skip dialogue input received"));
}

void AVNPlayerController::OnOpenMenu()
{
	UE_LOG(LogTemp, Log, TEXT("Open menu input received"));
}