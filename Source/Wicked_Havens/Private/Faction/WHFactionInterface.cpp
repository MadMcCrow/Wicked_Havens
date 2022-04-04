/* Copyright © Noé Perard-Gayot 2022. */


#include "Faction/WHFactionInterface.h"


void IWHFactionInterface::GetFaction_Implementation(FWHFaction& FactionRef) const
{
	if (auto AsObject = Cast<UObject>(this))
	{
		if (AsObject->GetOuter() && AsObject->GetOuter()->Implements<UWHFactionInterface>())
		{
			Execute_GetFaction(AsObject->GetOuter(),FactionRef);
		}
	}
	//FactionRef = FWHFaction();
}
