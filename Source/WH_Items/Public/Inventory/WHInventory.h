/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "WHInventory.generated.h"


class UWHItem;

/**
 *	A struct to contain a list of Items objects
 */
USTRUCT(BlueprintType, Category="Items")
struct WH_ITEMS_API FWHInventory

{
	GENERATED_BODY()

protected:
    /**
     * The map of items
     */
    UPROPERTY(BlueprintReadOnly, Category="Inventory")
    TMap<TObjectPtr<UWHItem>, int64> Items;



};
