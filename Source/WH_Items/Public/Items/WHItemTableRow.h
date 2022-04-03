/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WHItemTableRow.generated.h"

/**
 *	A table row to define an Item
 */
USTRUCT(BlueprintType, Category="Wicked Havens|Items")
struct WH_ITEMS_API FWHItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

    /** A tag to categorise this item */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FGameplayTag ItemTag;

    /** A class representing this item. not necessary, but useful , will default to WHItem */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta =(AllowedClasses="WHItem"))
    FSoftClassPath ItemClass;

};
