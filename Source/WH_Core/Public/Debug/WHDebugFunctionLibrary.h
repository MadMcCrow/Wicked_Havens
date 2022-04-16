/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "WHDebugFunctionLibrary.generated.h"

/**
 *	@class UWHDebugFunctionLibrary
 *	@brief	Function library for Action
 *	@todo : move all debug to another module ?
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|Actions")
class WH_CORE_API UWHDebugFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
