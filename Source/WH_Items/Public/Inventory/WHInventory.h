/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WHItem.generated.h"

/**
 *	A struct to contain a list of Items objects
 */
USTRUCT(BlueprintType,  ClassGroup=(WH), Category="Items")
struct WH_ITEMS_API FWHInventory

{
	GENERATED_BODY()

protected:
    /**
     * The map of items
     */
    UPROPERTY(BlueprintReadOnly, Category="Inventory")
    TMap<TObjectPtr<UWHItem>, uint64> Items;



};
