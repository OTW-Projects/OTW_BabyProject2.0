// © 2025 Open To Work - Samuel Abel

#include "Data/GameData.h"

FPrimaryAssetId UGameData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("GameData", GetFName());
}
