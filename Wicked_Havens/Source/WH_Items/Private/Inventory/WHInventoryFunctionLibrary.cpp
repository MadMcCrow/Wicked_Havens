/* Copyright © Noé Perard-Gayot 2022. */

#include "Inventory/WHInventoryFunctionLibrary.h"
#include "Items/WHItem.h"

void UWHInventoryFunctionLibrary::GetInventoryItems(const FWHInventory& Inventory, TMap<TObjectPtr<UWHItem>,uint64>& Items)
{
	Items.Empty();
	const auto& InventoryItems = Inventory.GetItems();
	for (const auto& Itr : InventoryItems)
	{
		Items.Add(Itr.Item, Itr.Count);
	}
}


void UWHInventoryFunctionLibrary::GetInventoryItems(const FWHInventory& Inventory, TMap<TSoftObjectPtr<UWHItem>,int64>& Items, bool& bSuccess)
{
	bSuccess = true;
	Items.Empty();
	const auto& InventoryItems = Inventory.GetItems();
	for (const auto& Itr : InventoryItems)
	{
		const auto SoftObjectPtr = TSoftObjectPtr<UWHItem>(Itr.Item.Get());
		if (SoftObjectPtr.IsNull())
		{
			bSuccess = false;
			continue;
		}
		if (Itr.Count >= static_cast<uint64>(TNumericLimits<int64>::Max()))
		{
			bSuccess = false;
			Items.Add(SoftObjectPtr, TNumericLimits<int64>::Max());
			continue;
		}
		// everything is fine, just add to your TMap
		Items.Add(SoftObjectPtr, Itr.Count);
	}
}

FWHInventory UWHInventoryFunctionLibrary::MakeInventoryFromItems(const TMap<TSoftObjectPtr<UWHItem>, int64>& Items)
{
	FWHInventory NewInventory;
	// Convert from BP-friendly to Inventory-ready
	TMap<TObjectPtr<UWHItem>, uint64> ObjPtrItems;
	for (const auto& ItemItr : Items)
	{
		if (ItemItr.Value > 0)
		{
			TObjectPtr<UWHItem> Item	= ItemItr.Key.LoadSynchronous();
			uint64 Amount				= static_cast<uint64>(ItemItr.Value);
			ObjPtrItems.Add(Item, Amount);
		}
	}
	NewInventory.InitItems(ObjPtrItems);
	return NewInventory;
}
