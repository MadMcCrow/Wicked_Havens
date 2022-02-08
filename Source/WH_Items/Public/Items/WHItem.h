/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Engine/DataAsset.h"
#include "WHItem.generated.h"

/**
 *	A table row to define an Item
 */
UCLASS(BlueprintType,  ClassGroup=(WH), Category="Items")
struct WH_ITEMS_API UWHItem : public UDataAsset

{
	GENERATED_BODY()

    /** A tag to categorise this item */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FDataTableRowHandle ItemHandle;

};
