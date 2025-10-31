// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataAsset.h"

const FPrimaryAssetType UCharacterDataAsset::CharacterAssetType = TEXT("CharacterDataAsset");

FPrimaryAssetId UCharacterDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(CharacterAssetType, GetFName());
}