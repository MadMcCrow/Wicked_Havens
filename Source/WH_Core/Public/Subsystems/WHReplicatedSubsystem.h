/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "WHReplicatedSubsystem.generated.h"


// forward declaration
class UWHReplicatedSubsystemComponent;

/**
 *	UWHReplicatedSubsystem
 *	@brief A WorldSubsystem that replicates over network
 */
UCLASS(Abstract, ClassGroup=(WH), Category="Core")
class WH_CORE_API UWHReplicatedSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	// <UTickableWorldSubsystem-API>
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Tick(float DeltaTime) override; 	/** called every frame */
	virtual TStatId GetStatId() const override; /** necessary for ticking */
	// <\UTickableWorldSubsystem-API>
	
	/**  the replication function, called via @see ReplicationComponent and GameState */
 	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

private:

	/** The component we track for replication */
	UPROPERTY()
	TObjectPtr<UWHReplicatedSubsystemComponent> ReplicationComponent;

};
