/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WHFaction.generated.h"

// forward declaration
struct FWHFactionDefinition;


/**
 *	@struct FWHFaction
 *	FWHFaction is a way to reference a faction to 
 */
USTRUCT(BlueprintType, Category="Wicked Havens|Faction")
struct WICKED_HAVENS_API FWHFaction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Faction", DisplayName="Faction ID")
	FName ID;

	/** get the FName directly. this is in fact the rowname of the faction DTB */
	operator FName() const {return ID;}

	/** Check if this faction exists */
	bool IsValid() const;

	/** return the informations about this faction */
	TOptional<FWHFactionDefinition> GetFactionData() const;
	
};



/**
 *	
 */
USTRUCT(BlueprintType, Category="Wicked Havens|Faction")
struct WICKED_HAVENS_API FWHFactionDefinition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Faction")
	FText FactionDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Faction")
	FText FactionDescription;
	
};

