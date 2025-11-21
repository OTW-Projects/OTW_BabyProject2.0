// © 2025 Open To Work - Samuel Abel

#include "Data/CharacterDataAsset.h"

const FPrimaryAssetType UCharacterDataAsset::CharacterAssetType = TEXT("CharacterDataAsset");

FPrimaryAssetId UCharacterDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(CharacterAssetType, GetFName());
}