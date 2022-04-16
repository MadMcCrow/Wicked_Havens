/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "WHActionFunctionLibrary.generated.h"

// forward declaration
class UInputMappingContext;
class UWHActionBase;
class APlayerController;
class UWHActionSubsystem;


/**
 *	@class UWHActionFunctionLibrary
 *	@brief	Function library for Action
 *	@todo : Change to TObjectPtr when supported by BP
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|Actions")
class WH_ACTION_API UWHActionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/**
	 *	Add an action for a player
	 *	All bindings will be done for you
	 */
	UFUNCTION(BlueprintCallable, Category="Actions")
	static void AddAction(APlayerController* PlayerController, UWHActionBase* InAction);

	/**
	 *	Remove an action for a player
	 *	we will remove all bindings and clean after you
	 */
	UFUNCTION(BlueprintCallable, Category="Actions")
	static void RemoveAction(APlayerController* PlayerController, UWHActionBase* InAction);

	/**
	 *	Get the action subsystem from the Player controller
	 *	PlayerController->LocalPlayer->Subsystem
	 *	it may fail because not all player controllers are local
	 */
	UFUNCTION(BlueprintCallable, Category="Actions")
	static UWHActionSubsystem* GetPlayerActionSubsystem(APlayerController* PlayerController);
	
};
