/* Copyright © Noé Perard-Gayot 2022. */


#include "Faction/WHFaction.h"
#include "Faction/WHFactionSettings.h"

bool FWHFaction::IsValid() const
{
	return UWHFactionSettings::IsValidFaction(*this);
}

TOptional<FWHFactionDefinition> FWHFaction::GetFactionData() const
{
	return UWHFactionSettings::GetFactionInfo(*this);
}


