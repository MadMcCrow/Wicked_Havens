/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHAttributeFunctionLibrary.generated.h"

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Inventory")
class WH_ATTRIBUTES_API UWHAttributeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
