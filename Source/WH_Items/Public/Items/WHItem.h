/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WHItem.generated.h"


/**
 *	@class UWHItem
 *	An Object representing an Item
 *	This is a base for having runtime informations about your items, like durability etc...
 */
UCLASS(Blueprintable, ClassGroup=(WH), Category="Wicked Havens|Items", Meta = (DisplayName="Item"))
class WH_ITEMS_API UWHItem : public UObject
{
	GENERATED_BODY()
	friend class UWHItemSubsystem;

public:

	/** Used by inventory, it checks for class and properties */
	virtual bool IsSame(const TObjectPtr<UWHItem> &OtherItem) const;

};
