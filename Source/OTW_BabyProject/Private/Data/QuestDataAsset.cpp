// © 2025 Open To Work - Samuel Abel

#include "Data/QuestDataAsset.h"

const FPrimaryAssetType UQuestDataAsset::QuestAssetType = TEXT("Quest");

FPrimaryAssetId UQuestDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(QuestAssetType, GetFName());
}

EQuestState UQuestDataAsset::GetCurrentQuestState() const
{
	return CurrentQuestState;
}

void UQuestDataAsset::SetCurrentQuestState(EQuestState NewQuestState)
{
	if (NewQuestState != CurrentQuestState)
	{
		this->CurrentQuestState = NewQuestState;
	}
}