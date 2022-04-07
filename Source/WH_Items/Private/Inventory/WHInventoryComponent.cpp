/* Copyright © Noé Perard-Gayot 2022. */

#include "Inventory/WHInventoryComponent.h"
#include "Net/UnrealNetwork.h"

UWHInventoryComponent::UWHInventoryComponent() : Super()
{
	Items.OnItemAddedDelegate.AddWeakLambda(this, [this](auto Item, int64 Count){ OnItemAdded.Broadcast(Item,Count);});
	Items.OnItemChangedDelegate.AddWeakLambda(this, [this](auto Item, int64 Count){ OnItemChanged.Broadcast(Item,Count);});
	Items.OnItemRemovedDelegate.AddWeakLambda(this, [this](auto Item, int64 Count){	OnItemRemoved.Broadcast(Item,Count);});
}

void UWHInventoryComponent::BeginDestroy()
{
	OnItemAdded.Clear();
	OnItemChanged.Clear();
	OnItemRemoved.Clear();
	Super::BeginDestroy();
}

void UWHInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHInventoryComponent,Items);
}
