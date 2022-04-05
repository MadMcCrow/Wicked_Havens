/* Copyright © Noé Perard-Gayot 2022. */

#include "Settings/WHItemSettings.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"

FSimpleDelegate UWHItemSettings::LoadDatable() const
{
	FSimpleDelegate Del;
	if (ItemDatatable.IsNull())
		return Del;
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	Streamable.RequestAsyncLoad(ItemDatatable, Del);
	return Del;
}

UDataTable* UWHItemSettings::GetDatatable() const
{
	return Cast<UDataTable>(ItemDatatable.ResolveObject());
}
