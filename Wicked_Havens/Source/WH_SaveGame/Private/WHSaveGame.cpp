// Fill out your copyright notice in the Description page of Project Settings.


#include "WHSaveGame.h"

#include "Kismet/GameplayStatics.h"

void UWHSaveGame::AddSlot(const FName& Slot, const int32 UserIndex, const TArray<uint8>& ExtraInfo)
{
	Saves.AddUnique(FWHSaveData(Slot, FDateTime::Now(), UserIndex, ExtraInfo));
}

TArray<FWHSaveData> UWHSaveGame::GetGameSaves() const
{
	return Saves;
}

UWHSaveGame* UWHSaveGame::CreateWHSaveGame()
{
	return Cast<UWHSaveGame>(UGameplayStatics::CreateSaveGameObject(UWHSaveGame::StaticClass()));
}
