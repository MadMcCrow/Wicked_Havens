/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHFaction.h"
#include "WHFactionSettings.generated.h"


/**
 *	@class UWHFactionSettings
 *	@brief Set the various factions of the game there
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName= Factions), Category="Wicked Havens|Factions", MinimalAPI)
class UWHFactionSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
		virtual FName GetCategoryName() const override {return FName("Wicked Havens");}
protected:
	/**
     *	A datatable containing all the Factions
     */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Items", meta=( AllowedClasses="DataTable", RowType = "WHTableRowFaction"), DisplayName = "Factions")
	FSoftObjectPath FactionDatatablePath;

	/** the first time it loads the datatable, then it just returns it */
	static UDataTable* GetFactionDatatable();

public:

	/** Get the information about a Faction */
	static TOptional<FWHFactionDefinition> GetFactionInfo(const FWHFaction& Faction) ;

	/** Check that we have a valid faction with this data */
	static bool IsValidFaction(const FWHFaction& Faction);

private:

	UPROPERTY(Transient)
	class UDataTable* FactionDatatable;
	
};

