// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WHSaveGame.h"
#include "WHSaveGameSubsystem.generated.h"

/**
 *	UWHSaveGameSubsystem :
 *							Subsystem to allow composite saves aka. Sub-slots.
 *	@todo  use in memory save until we deinitialize
 */
UCLASS(MinimalAPI, Category = "SaveGame", ClassGroup = WH_SaveGame, BlueprintType)
class UWHSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Subsystem API
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//\Subsystem API


		// Change Master Slot
	UFUNCTION()
	void SetMasterSlot(const FName& NewMasterSlot);


	// Change Master Slot
	UFUNCTION()
	void SetUserIndex(const int32 &NewUserIndex);


	/**
	 * Load all the information about our "sub" slots
	 *
	 * @param SaveGame			The save game you wanna save
	 * @param Slot				Name of your "sub" slot
	 * @param SaveExtraInfo		Extra information as raw byte you want to add to your save (optional)
	 */
	void SaveGame(USaveGame* SaveGame, const FName& Slot, const TArray<uint8>& SaveExtraInfo = TArray<uint8>());

	/**
	 * Load all the information about our "sub" slots
	 *
	 * @return					the list of sub slot found with those two parameters
	 */
	TArray<FWHSaveData> GetAllSaveData() const;

	/**
	 * Load a "sub-slots"
	 *
	 * @param SaveData			infos about the slot to load
	 * @return					the list of sub slot found with those two parameters
	 */
	USaveGame* LoadSaveData(const FWHSaveData& SaveData) const;

private:

	// Name of the master save we currently have in memory
	UPROPERTY(Transient)
	FName MasterSlot;

	// Current UserIndex
	UPROPERTY(Transient)
	int32 UserIndex;

	// Save Game stored in memory until we write them to disk
	TMap<FWHSaveData, TArray<uint8>> InMemorySaves;

	// Write all In memory
	UFUNCTION()
	void WriteInMemorySaveToDisk();


};

//WH_SAVEGAME_API