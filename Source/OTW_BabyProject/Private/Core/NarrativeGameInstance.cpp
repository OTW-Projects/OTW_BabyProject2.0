// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NarrativeGameInstance.h"

void UNarrativeGameInstance::Init()
{
	Super::Init();

	if (!NarrativeManager)
	{
		NarrativeManager = NewObject<UNarrativeManager>(this);
	}
}