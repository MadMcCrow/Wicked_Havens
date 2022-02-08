/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "Subsystems/ReplicatedSubsystem.h"
#include "WHGameEventSubsystem.generated.h"

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="GameEvent")
class WH_CORE_API UWHGameEventSubsystem : public ReplicatedSubsystem
{
	GENERATED_BODY()

public:

};
