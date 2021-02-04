// Fill out your copyright notice in the Description page of Project Settings.

#include "WHSaveGameStatics.h"
#include "WHSaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"

TArray<FWHSaveData> UWHSaveGameStatics::GetAllSaveData(const UObject* WorldContextObject)
{
	if (auto SaveSystem = GetSaveGameSubsystem(WorldContextObject))
	{
		return SaveSystem->GetAllSaveData();
	}
	return TArray<FWHSaveData>();
}

USaveGame* UWHSaveGameStatics::LoadSaveData(const UObject* WorldContextObject, const FWHSaveData& SaveData)
{
	if (auto SaveSystem = GetSaveGameSubsystem(WorldContextObject))
	{
		return SaveSystem->LoadSaveData(SaveData);
	}
	return nullptr;
}


void UWHSaveGameStatics::SaveGame(const UObject* WorldContextObject, USaveGame* SaveGame, const FName& Slot, const TArray<uint8>& ExtraInfo)
{
	if (auto SaveSystem = GetSaveGameSubsystem(WorldContextObject))
	{
		SaveSystem->SaveGame( SaveGame, Slot, ExtraInfo);
	}
}

void UWHSaveGameStatics::InitSystemForUser(const UObject* WorldContextObject, const FName& NewMasterSlot, const int32& NewUserIndex)
{
	if (auto SaveSystem = GetSaveGameSubsystem(WorldContextObject))
	{
		SaveSystem->SetMasterSlot(NewMasterSlot);
		SaveSystem->SetUserIndex(NewUserIndex);
	}
}

UWHSaveGameSubsystem* UWHSaveGameStatics::GetSaveGameSubsystem(const UObject* WorldContextObject)
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if (auto SaveSystem = GameInstance->GetSubsystem<UWHSaveGameSubsystem>())
		{
			return SaveSystem;
		}
	}
	return nullptr;
}