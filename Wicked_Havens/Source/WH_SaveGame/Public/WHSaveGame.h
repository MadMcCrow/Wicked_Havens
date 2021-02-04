// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WHSaveGame.generated.h"


/**
 *  Minimalistic infos about a save
 */
USTRUCT(BlueprintType)
struct FWHSaveData
{
	GENERATED_BODY()
	friend class UWHSaveGame;
	friend class UWHSaveGameSubsystem;

protected:

	// (hopefully) Unique name for this slot
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	FName Slot;

	// User index might be used on certain platform
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	int32 UserIndex;

	// Time of save
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	FDateTime Time;

	// Allows to store extra info as serialized bytes
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly)
	TArray<uint8> ExtraInfo;


public:

	// default ctr
	FWHSaveData(): UserIndex(0)
	{
	}

	// parametric ctr
	FWHSaveData(const FName &SaveSlot,const FDateTime &SaveTime, const int32 SaveUserIndex, const TArray<uint8>& SaveExtraInfo = TArray<uint8>())
		: Slot(SaveSlot), UserIndex(SaveUserIndex), Time(SaveTime), ExtraInfo(SaveExtraInfo)
	{}

	// neither time, nor extra info are necessary for comparison, we allow overwrite
	bool operator==(const FWHSaveData &Other) const
	{
		return Slot == Other.Slot && UserIndex && Other.UserIndex;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FWHSaveData& s)
	{
		return GetTypeHash(s.Slot)* GetTypeHash(s.UserIndex);
	}

};


/**
 *	Allows to have multiple "sub-saves"
 *	this will save your saves, while making sure not to allow for three levels of recursion
 */
UCLASS(MinimalAPI, Category="SaveGame", ClassGroup=WH_SaveGame)
class UWHSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void AddSlot(const FName &Slot, const int32 UserIndex = 0, const TArray<uint8>& ExtraInfo = TArray<uint8>());

	UFUNCTION()
	TArray<FWHSaveData> GetGameSaves() const;

	UFUNCTION()
	static UWHSaveGame* CreateWHSaveGame();

private:

	// The name of the slot we saved
	UPROPERTY(SaveGame)
	TArray<FWHSaveData> Saves;


};
