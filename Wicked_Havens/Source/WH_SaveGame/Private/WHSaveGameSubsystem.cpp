// Fill out your copyright notice in the Description page of Project Settings.


#include "WHSaveGameSubsystem.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


void UWHSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InMemorySaves.Empty();
	MasterSlot = FName("DefaultSaveSlot");
	UserIndex = 0;
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (APlayerState* PS = PC->GetPlayerState<APlayerState>())
		{
			// this will match SteamID if using Steam :)
			UserIndex = PS->GetPlayerId();
		}
	}

}

void UWHSaveGameSubsystem::Deinitialize()
{
	// write to file all unsaved slots
	WriteInMemorySaveToDisk();

	// finally call super
	Super::Deinitialize();
}

void UWHSaveGameSubsystem::SetMasterSlot(const FName& NewMasterSlot)
{
	if (NewMasterSlot != MasterSlot)
	{
		// first save master to disk with InMemory info
		WriteInMemorySaveToDisk();
		// Change master value
		MasterSlot = NewMasterSlot;
	}
}

void UWHSaveGameSubsystem::SetUserIndex(const int32& NewUserIndex)
{
	if (NewUserIndex != UserIndex)
	{
		WriteInMemorySaveToDisk();
		UserIndex = NewUserIndex;
	}
}

void UWHSaveGameSubsystem::SaveGame(USaveGame* SaveGame, const FName& Slot, const TArray<uint8> & SaveExtraInfo)
{
	// Save to memory
	TArray<uint8> SaveRaw;
	UGameplayStatics::SaveGameToMemory(SaveGame, SaveRaw);

	InMemorySaves.Add(FWHSaveData(Slot, FDateTime::Now(), UserIndex, SaveExtraInfo), SaveRaw);
}

TArray<FWHSaveData> UWHSaveGameSubsystem::GetAllSaveData() const
{
	TArray<FWHSaveData> InMemory, OnDisk;
	InMemorySaves.GenerateKeyArray(InMemory);
	if (UWHSaveGame* MasterSave = Cast<UWHSaveGame>(UGameplayStatics::LoadGameFromSlot(MasterSlot.ToString(), UserIndex)))
	{
		OnDisk = MasterSave->GetGameSaves();
	}
	for (FWHSaveData itr : OnDisk)
	{
		InMemory.AddUnique(itr);
	}
	return InMemory;
}

USaveGame* UWHSaveGameSubsystem::LoadSaveData(const FWHSaveData& SaveData) const
{
	// Try to load from memory first
	if (auto RawSaveDataPtr = InMemorySaves.Find(SaveData) )
	{
		if (USaveGame* Save = UGameplayStatics::LoadGameFromMemory(*RawSaveDataPtr))
		{
			return Save;
		}
	}
	// try with user index from SaveData
	if (USaveGame* Save = UGameplayStatics::LoadGameFromSlot(SaveData.Slot.ToString(), SaveData.UserIndex))
	{
		return Save;
	}
	// fallback to our UserIndex
	return  UGameplayStatics::LoadGameFromSlot(SaveData.Slot.ToString(), UserIndex);
}

void UWHSaveGameSubsystem::WriteInMemorySaveToDisk()
{
	UWHSaveGame* MasterSave = UWHSaveGame::CreateWHSaveGame();
	for (TTuple<FWHSaveData, TArray<uint8>> itr : InMemorySaves)
	{
		UGameplayStatics::SaveDataToSlot(itr.Value, itr.Key.Slot.ToString(), itr.Key.UserIndex);
		MasterSave->AddSlot(itr.Key.Slot, itr.Key.UserIndex, itr.Key.ExtraInfo);
	}
	UGameplayStatics::SaveGameToSlot(MasterSave, MasterSlot.ToString(), UserIndex);
	InMemorySaves.Empty();
}