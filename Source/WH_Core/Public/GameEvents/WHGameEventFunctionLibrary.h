/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHGameEventFunctionLibrary.generated.h"


// forward declaration
class UWHGameEvent;

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="GameEvents")
class WH_CORE_API UWHGameEventFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	 *	LaunchGameEvent
	 *	Tries to start a GameEvent
	 *	@param WorldContextObject	WorldContextPin
	 *	@param	EventClass			The class of event to run
	 *	@param	Source				Actor making the request
	 *	@param	Target				Actor concerned by the result
	 */
	UFUNCTION(BlueprintCallable, Category="GameEvent", meta=(WorldContext = "WorldContextObject"))
	static void LaunchGameEvent(const UObject* WorldContextObject, UPARAM(meta=(AllowedClasses="WHGameEvent")) FSoftClassPath EventClass, AActor * Source, AActor* Target);


};
