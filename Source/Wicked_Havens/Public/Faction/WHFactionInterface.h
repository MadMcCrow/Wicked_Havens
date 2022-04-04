/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WHFaction.h"
#include "WHFactionInterface.generated.h"

/**
 *	@interface UWHFactionInterface
 *	Interface to add a faction to an object.
 *	Factions are only considered during fights
 */
UINTERFACE(Category="Wicked Havens|Faction")
class WICKED_HAVENS_API UWHFactionInterface : public UInterface
{
	GENERATED_BODY()
};

class WICKED_HAVENS_API IWHFactionInterface
{
	GENERATED_BODY()
	
public:
	/** Function to implement in your classes */
	UFUNCTION(BlueprintNativeEvent, Category="Faction")
	void GetFaction(FWHFaction& FactionRef) const;
	virtual void GetFaction_Implementation(FWHFaction& FactionRef) const;
};