/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WHItemTableRow.generated.h"

/**
 *	@struct FWHItemTableRow
 *	the main struct to define all items in the settings
 *	@todo :
 *		- Add all generic information about items here.
 */
USTRUCT(BlueprintType, Category="Wicked Havens|Items")
struct WH_ITEMS_API FWHItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

    /** A class representing this item. not necessary, but useful , will default to WHItem */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta =(AllowedClasses="WHItem"))
    FSoftClassPath ItemClass;

	/** A tag to categorise this item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FGameplayTag ItemTag;

};
