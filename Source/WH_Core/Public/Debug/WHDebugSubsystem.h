/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Subsystems/WHPlayerTickSubsystem.h"
#include "WHDebugSubsystem.generated.h"


/**
 *	@class UWHDebugSubsystem
 *	@brief	Subsystem adding debug info on screen
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Debug", MinimalAPI)
class UWHDebugSubsystem : public UWHPlayerTickSubsystem
{
	GENERATED_BODY()
	
public:

	// <ULocalPlayerSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// <\ULocalPlayerSubsystem-API>

	/** Called every frame : */
	virtual void Tick(float DeltaTime) override;

private:

	TSharedPtr<SVerticalBox> DebugContainer;
	
	void InitDebugWidgets();
	
	
};



