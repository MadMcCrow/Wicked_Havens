/* Copyright © Noé Perard-Gayot 2022. */

#include "Inventory/WHInventory.h"

void FWHInventoryItem::Serialize(FArchive& Ar)
{
	Ar << Item;
	Ar << Count;
}

void FWHInventoryItem::PreReplicatedRemove(const FWHInventory& InArraySerializer)
{
	InArraySerializer.OnItemRemovedDelegate.Broadcast(Item,Count);
}

void FWHInventoryItem::PostReplicatedAdd(const FWHInventory& InArraySerializer)
{
	InArraySerializer.OnItemAddedDelegate.Broadcast(Item,Count);
}

void FWHInventoryItem::PostReplicatedChange(const FWHInventory& InArraySerializer)
{
	InArraySerializer.OnItemChangedDelegate.Broadcast(Item,Count);
}

bool FWHInventory::Serialize(FArchive& Ar)
{
	// just use Unreal internal method, I guess
	Ar << Items;
	// Should preform a few checks maybe...
	return true;
}

bool FWHInventory::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Serialize(Ar);
}

bool FWHInventory::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FastArrayDeltaSerialize<FWHInventoryItem>( Items, DeltaParms, *this );
}

void FWHInventory::InitItems(const TMap<TObjectPtr<UWHItem>, uint64> InItems)
{
	for (auto ItemItr: InItems)
	{
		if(ItemItr.Value > 0)
		{
			Items.Add(FWHInventoryItem(ItemItr.Key, ItemItr.Value));
		}
	}
	MarkArrayDirty();
}

FWHInventoryItem* FWHInventory::AddItem(const TObjectPtr<UWHItem>& ItemObject, uint64 Count)
{
	if (FWHInventoryItem* FoundPtr = Items.FindByPredicate([ItemObject] (const FWHInventoryItem& ItemItr)
	{
		return ItemItr.Item == ItemObject;
	}))
	{
		FoundPtr->Count += Count;
		MarkItemDirty(*FoundPtr);
		return FoundPtr;
	}
	else
	{
		if (Count > 0)
		{
			FWHInventoryItem& NewItemRef = Items.Add_GetRef(FWHInventoryItem(ItemObject,Count));
			MarkItemDirty(NewItemRef);
			MarkArrayDirty();
			return &NewItemRef;
		}
	}
	return nullptr;
}

bool FWHInventory::RemoveItem(const TObjectPtr<UWHItem>& ItemObject, uint64 Count)
{
	if (FWHInventoryItem* FoundPtr = Items.FindByPredicate([ItemObject] (const FWHInventoryItem& ItemItr)
		{
			return ItemItr.Item == ItemObject;
		}))
	{
		uint64 NewCount = FMath::Max(0ull, FoundPtr->Count - Count);
		if (NewCount > 0)
		{
			FoundPtr->Count = NewCount;
			MarkItemDirty(*FoundPtr);
			return true;
		}
		else
		{
			Items.Remove(*FoundPtr);
			MarkArrayDirty();
			return true;
		}

	}
	else
	{
		// tried to remove sothing that was not present
		return false;
	}
}