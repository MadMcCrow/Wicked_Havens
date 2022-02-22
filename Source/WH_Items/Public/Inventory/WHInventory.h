/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "WHInventory.generated.h"


// forward declaration
class UWHItem;

DECLARE_MULTICAST_DELEGATE_TwoParams(FWHInventoryDelegate,TObjectPtr<UWHItem>, int64)

/**
 *	An Item for @see FWHInventory
 *	Specifically adapted to fast replication
 */
USTRUCT()
struct WH_ITEMS_API FWHInventoryItem : public FFastArraySerializerItem
{
	GENERATED_BODY()
	friend struct FWHInventory;

private:
	/**
	 *	CTR : Count will be zero if invalid item is passed
	 *	zero count item will not be added, nor replicated
	 */
	FWHInventoryItem(const TObjectPtr<UWHItem>& InObject, uint64 InCount)
	: Item(InObject)
	, Count(InObject.IsNull() ? 0 : InCount)
	{
	}

public:

	// this won't be valid, so don't bother
	FWHInventoryItem() = default;

	/** The exact item we have @see UWHItem */
	UPROPERTY()
	TObjectPtr<UWHItem> Item;

	/** How many of this exact item do we have */
	UPROPERTY()
	uint64 Count;

	/** Called by NetSerialize of FWHInventory */
	void Serialize(FArchive& Ar);

	/**
	 * Optional functions for client side notification of changes to items;
	 * NOTE: It is not safe to modify the contents of the array serializer within these functions, nor to rely on the contents of the array
	 * being entirely up-to-date as these functions are called on items individually as they are updated, and so may be called in the middle of a mass update.
	 */
	void PreReplicatedRemove(const struct FWHInventory& InArraySerializer);
	void PostReplicatedAdd(const struct FWHInventory& InArraySerializer);
	void PostReplicatedChange(const struct FWHInventory& InArraySerializer);

	// comparison operator for Array operations
	bool operator==(const FWHInventoryItem& Other) const {return Item == Other.Item && Count == Other.Count;}

};

/**
 *	A struct to contain a list of Items objects
 */
USTRUCT(BlueprintType, Category = "Items", meta = (HasNativeBreak = "WH_Items.WHInventoryFunctionLibrary.GetInventoryItems", HasNativeMake = "WH_Items.WHInventoryFunctionLibrary.MakeInventoryFromItems"))
struct WH_ITEMS_API FWHInventory : public FFastArraySerializer
{
	GENERATED_BODY()
public:

	// Begin Serialization -----
	bool Serialize(FArchive& Ar);
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);
	// End Serialization -----


	/**
	 *	Add an item to this inventory, and return a reference to it
	 *	We will change the owner of that item to us. if it was in an inventory, we'll remove it from it
	 */
	void InitItems(const TMap<TObjectPtr<UWHItem>, uint64> InItems);

	/**
	 *	Add an item to this inventory, and return a reference to it
	 *	We will change the owner of that item to us. if it was in an inventory, we'll remove it from it
	 */
	FWHInventoryItem* AddItem(const TObjectPtr<UWHItem>& ItemObject, uint64 Count);

	/**
	 *	Remove item from this inventory
	 *	@return true if no error encountered
	 */
	bool RemoveItem(const TObjectPtr<UWHItem>& ItemObject, uint64 Count);

	/** Fast getter */
	FORCEINLINE const TArray<FWHInventoryItem>& GetItems() const  {return Items;}

private:
    /**
     * The map of items
     */
    UPROPERTY()
    TArray<FWHInventoryItem> Items;

public:

	FWHInventoryDelegate OnItemChangedDelegate;
	FWHInventoryDelegate OnItemRemovedDelegate;
	FWHInventoryDelegate OnItemAddedDelegate;

};


/** Specify custom functions to look for in FWHInventory */
template<>
struct TStructOpsTypeTraits<FWHInventory> : public TStructOpsTypeTraitsBase2<FWHInventory>
{
	enum
	{
		WithSerializer                 = true,                         // struct has a Serialize function for serializing its state to an FArchive.
		WithNetSerializer              = true,                         // struct has a NetSerialize function for serializing its state to an FArchive used for network replication.
		WithNetDeltaSerializer         = true,                         // struct has a NetDeltaSerialize function for serializing differences in state from a previous NetSerialize operation.
	};
};
