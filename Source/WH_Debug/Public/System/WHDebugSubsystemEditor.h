/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHDebugSubsystemInterface.h"
#include "Subsystems/UnrealEditorSubsystem.h"
#include "WHDebugSubsystemEditor.generated.h"

/**
 *	@class UWHDebugSubsystemGame
 *	@brief	Displays Debug widgets during gameplay
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Debug", MinimalAPI)
class UWHDebugSubsystemEditor : public UUnrealEditorSubsystem, public IWHDebugSubsystemInterface
{
	GENERATED_BODY()
	
public:

	// <ULocalPlayerSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// <\ULocalPlayerSubsystem-API>
	
};


