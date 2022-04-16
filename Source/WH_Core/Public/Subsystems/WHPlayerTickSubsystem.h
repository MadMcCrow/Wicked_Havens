/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Tickable.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WHPlayerTickSubsystem.generated.h"


/**
 *	@class UWHPlayerTickSubsystem
 *	@brief A Local Player subsystem 
 */
UCLASS(Abstract, ClassGroup=(WH), Category="Core")
class WH_CORE_API UWHPlayerTickSubsystem : public ULocalPlayerSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	// <USubsystem-API>
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// <\USubsystem-API>

	//<FTickableGameObject-API>
	virtual void Tick(float DeltaTime) override; 	/** called every frame */
	virtual TStatId GetStatId() const override; /** necessary for ticking */
	virtual bool IsAllowedToTick() const override { return IsInitialized(); }
	//<\FTickableGameObject-API>

	/**	Simpler getter for subclasses	*/
	FORCEINLINE const bool& IsInitialized() const {return bInitialized;}

private:

	UPROPERTY(Transient)
	bool bInitialized = true;
};
