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
UCLASS(Blueprintable, BlueprintType,  ClassGroup=(WH), Category="Items")
class WH_ITEMS_API UWHItem : public UObject
{
	GENERATED_BODY()
	friend class UWHItemSubsystem;

public:

	/** Used by inventory, it checks for class and properties */
	virtual bool IsSame(const TObjectPtr<UWHItem> &OtherItem) const;

	/**
	 *	GetRowHandle
	 *	Get @see ItemHandle in a const fashion (only UWHItemSubsystem should edit it)
	 */
	UFUNCTION(BlueprintPure, Category = "Item")
	const FDataTableRowHandle& GetRowHandle() const {return ItemHandle;}

protected:

	/** shortcut for custom functions */
	TOptional<struct FWHItemTableRow> GetItemRow() const;

private:

	/** called by UWHItemSubsystem @see ItemHandle */
	void SetItemHandle(UDataTable* Table, FName Row);

    /** This handle is set by UWHItemSubsystem on generation @see SetItemHandle */
    UPROPERTY(Transient)
    FDataTableRowHandle ItemHandle;

};
