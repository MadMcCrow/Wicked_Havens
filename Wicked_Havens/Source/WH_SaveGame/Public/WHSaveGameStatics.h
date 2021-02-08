// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHSaveGame.h"
#include "WHSaveGameStatics.generated.h"

/**
 *	UWHSaveGameStatics :
 *							Exposed statics to have save game in your game
 */
UCLASS( Category = "SaveGame", ClassGroup = WH_SaveGame, BlueprintType)
class WH_SAVEGAME_API UWHSaveGameStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Load all the information about our "sub-slots"
	 *
	 * @return					the list of sub slot found with those two parameters
	 */
	UFUNCTION(BlueprintPure, Category = "SaveGame", meta = (WorldContext = "WorldContextObject"))
	static TArray<FWHSaveData>  GetAllSaveData(const UObject* WorldContextObject);

	/**
	 * Load a "sub-slots"
	 *
	 * @param SaveData			infos about the slot to load
	 * @param UserIndex			For some platforms, master user index to identify the user doing the saving.
	 * @return					the list of sub slot found with those two parameters
	 */
	UFUNCTION(BlueprintPure, Category = "SaveGame", meta = (WorldContext = "WorldContextObject"))
	static USaveGame* LoadSaveData(const UObject* WorldContextObject, const FWHSaveData& SaveData);

	/**
	 * Load a "sub-slots"
	 *
	 * @param SaveData			infos about the slot to load
	 * @param ExtraInfo			details you want to add
	 * @return					the list of sub slot found with those two parameters
	 */
	UFUNCTION(BlueprintPure, Category = "SaveGame", meta = (WorldContext = "WorldContextObject"))
	static void SaveGame(const UObject* WorldContextObject, USaveGame* SaveGame, const FName& Slot,const TArray<uint8> &ExtraInfo);


	/**
	 * Change Master slot name, the master save will be saved in a different slot
	 *
	 * @param NewMasterSlot		The name of the MasterSlot for this user
	 * @param NewUserIndex		The unique user index for this save
	 */
	UFUNCTION(BlueprintPure, Category = "SaveGame", meta = (WorldContext = "WorldContextObject"))
	static void InitSystemForUser(const UObject* WorldContextObject, const FName& NewMasterSlot, const int32& NewUserIndex);

protected:

	/**
	 * Get SaveGame subsystem
	 */
	UFUNCTION(BlueprintPure, Category = "SaveGame", meta = (WorldContext = "WorldContextObject"))
	static class UWHSaveGameSubsystem* GetSaveGameSubsystem(const UObject* WorldContextObject);

};