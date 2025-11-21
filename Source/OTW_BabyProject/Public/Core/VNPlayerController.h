// © 2025 Open To Work - Samuel Abel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VNPlayerController.generated.h"

class UUserWidget;
class UNarrativeManager;

UCLASS(Blueprintable, BlueprintType)
class OTW_BABYPROJECT_API AVNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVNPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UFUNCTION(BlueprintPure, Category = "UI")
	TSubclassOf<UUserWidget> GetWidgetClass() const { return WidgetClass; }

	UFUNCTION(BlueprintPure, Category = "UI")
	UUserWidget* GetMainWidget() const { return MainWidget; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainWidget;
	
	// Input handlers
	void OnNextDialogue();
	void OnSkipDialogue();
	void OnOpenMenu();

	// Helper to get game systems
	UNarrativeManager* GetNarrativeManager() const;
};
