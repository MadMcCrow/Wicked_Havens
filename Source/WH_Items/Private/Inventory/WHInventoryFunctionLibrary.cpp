/* Copyright © Noé Perard-Gayot 2021. */

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
