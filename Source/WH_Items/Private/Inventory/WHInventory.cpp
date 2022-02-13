/* Copyright © Noé Perard-Gayot 2021. */

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
	int64 Count = 0;
	if (Ar.IsLoading())
	{
		Ar << Count; // read from Archive;
		Items.SetNum(Count);
	}
	else
	{
		Count = Items.Num();
		Ar << Count; // write to Archive;
	}
	for (int64 idx = Count; idx-->0;)
	{
		Items[idx].Serialize(Ar);
	}
	// Should preform a few checks maybe...
	return true;
}

bool FWHInventory::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Serialize(Ar);
}

bool FWHInventory::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FWHInventoryItem, FWHInventory>( Items, DeltaParms, *this );
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
