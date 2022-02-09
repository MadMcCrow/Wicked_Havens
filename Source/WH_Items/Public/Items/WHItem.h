/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "WHItem.generated.h"

/**
 *	A unique asset
 */
UCLASS(BlueprintType,  ClassGroup=(WH), Category="Items")
class WH_ITEMS_API UWHItem : public UDataAsset
{
	GENERATED_BODY()
	friend class UWHItemSubsystem;

public:



private:
    /** A tag to categorise this item */
    UPROPERTY()
    FDataTableRowHandle ItemHandle;

};
