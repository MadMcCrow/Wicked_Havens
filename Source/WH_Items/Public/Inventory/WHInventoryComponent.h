/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHInventory.h"
#include "Engine/NetSerialization.h"
#include "WHInventoryComponent.generated.h"

/**
 *	Blueprint-Friendly event for inventory
 *	@note : ObjectPtr is not yet compatible with Dynamic delegate, so pointer safety is not good
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWHInventoryEvent,UWHItem*, Item, int64, Count);

/**
 *	@class UWHInventoryComponent
 *	Component for Actors that need an Inventory
 *	@todo
 *		- Add the init capability
 *		- Add the equipment system
 *		- add the possibility to refuse adding items
 */
UCLASS(BlueprintType, ClassGroup=(WH), Category="Wicked Havens|Items", Meta = (BlueprintSpawnableComponent, DisplayName="Inventory Component"))
class WH_ITEMS_API UWHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// CTR
	UWHInventoryComponent();

	// <UActorComponent-API>
	virtual void BeginDestroy() override; /** Make sure that events are not called anymore */
	// <\UActorComponent-API>
private:

	/**
	 *	Inventory is the array containing the items
	 *	@note
	 *		- Replicated
	 *		- Optimized for storage, add events
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category="Items", meta=(AllowPrivateAccess))
	FWHInventory Items;


public:

	/** event from @see Items */
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category="Items", DisplayName="On Item Added")
	FWHInventoryEvent OnItemAdded;

	/** event from @see Items */
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category="Items", DisplayName="On Item Changed")
	FWHInventoryEvent OnItemChanged;

	/** event from @see Items */
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category="Items", DisplayName="On Item Removed")
	FWHInventoryEvent OnItemRemoved;
	
};
