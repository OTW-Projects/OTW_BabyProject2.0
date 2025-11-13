// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NarrativeGameInstance.h"

void UNarrativeGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("NarrativeGameInstance: Initialized"));
	
	// Future: Load saved game data here
	// Future: Initialize persistent systems here
}