/* Copyright © Noé Perard-Gayot 2022. */


#include "Faction/WHFactionSettings.h"


UDataTable* UWHFactionSettings::GetFactionDatatable()
{
	if (const auto Settings = GetMutableDefault<UWHFactionSettings>())
	{
		if (!Settings->FactionDatatable)
		{
			Settings->FactionDatatable = Cast<UDataTable>(Settings->FactionDatatablePath.TryLoad());
		}
		return Settings->FactionDatatable;
	}
	return nullptr;
}

TOptional<FWHFactionDefinition> UWHFactionSettings::GetFactionInfo(const FWHFaction& Faction)
{
	if (const auto Datatable = GetFactionDatatable())
	{
		if (const auto Found = Datatable->FindRow<FWHFactionDefinition>(Faction, TEXT("UWHFactionSettings::GetFactionInfo")))
		{
			return *Found;
		}
	}
	return {};
}

bool UWHFactionSettings::IsValidFaction(const FWHFaction& Faction)
{
	if (const auto Datatable = GetFactionDatatable())
	{
		return Datatable->GetRowNames().Contains(Faction);
	}
	return false;
}
