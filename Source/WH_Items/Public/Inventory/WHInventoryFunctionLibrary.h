/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inventory/WHInventory.h"
#include "WHInventoryFunctionLibrary.generated.h"

// forward declarations
class UWHItem;

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Inventory")
class WH_ITEMS_API UWHInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	 *	Retrieve the Items in an inventory as a TMap for easier usage
	 *	This cannot be Blueprintable, because uint64 and TObjectPtr are not supported
	 */
	static void GetInventoryItems(const FWHInventory& Inventory, TMap<TObjectPtr<UWHItem>,uint64>& Items);

	/**
	 *	Blueprint-friendly version of the one before
	 *	bSuccess is false if anything went wrong
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory", meta = (NativeBreakFunc, AdvancedDisplay=2))
	static void GetInventoryItems(const FWHInventory& Inventory, TMap<TSoftObjectPtr<UWHItem>,int64>& Items, bool& bSuccess);

	/**
	 *	Make Function for inventory
	 *	Expose initiating inventory to blueprint
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory", meta = (NativeMakeFunc))
	static struct FWHInventory MakeInventoryFromItems(const TMap<TSoftObjectPtr<UWHItem>,int64>& Items);

	// TODO : Add Item, remove Item, Get Item Count, etc...
};
