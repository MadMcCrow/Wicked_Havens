/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHDebugSubsystemInterface.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WHDebugSubsystemGame.generated.h"

/**
 *	@class UWHDebugSubsystemGame
 *	@brief	Displays Debug widgets during gameplay
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Debug", MinimalAPI)
class UWHDebugSubsystemGame : public ULocalPlayerSubsystem, public IWHDebugSubsystemInterface
{
	GENERATED_BODY()
	
public:

	// <ULocalPlayerSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// <\ULocalPlayerSubsystem-API>
	

	/** Get the player controller out of the */
	TObjectPtr<APlayerController> GetPlayerController() const;
};


