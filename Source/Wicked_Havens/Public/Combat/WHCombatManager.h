/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Subsystems/WHReplicatedSubsystem.h"
#include "WHCombatManager.generated.h"


/**
 *	@class UWHCombatManager
 *	a class responsible for deciding who damages who and how much.
 *	this is replicated so everyone gets the same results
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|Combat", Meta = (DisplayName="Combat Manager"))
class WICKED_HAVENS_API UWHCombatManager : public UWHReplicatedSubsystem
{
	GENERATED_BODY()

};
