// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "VNPlayerController.generated.h"


UCLASS(Blueprintable, BlueprintType)
class OTW_BABYPROJECT_API AVNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AVNPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> WidgetClass;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	UPROPERTY()
	UUserWidget* CurrentWidget;
	
	void OnNextDialogue();
	void OnSkipDialogue();
	void OnOpenMenu();
};
