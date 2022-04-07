/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Tickable.h"
#include "Subsystems/WorldSubsystem.h"
#include "WHReplicatedSubsystem.generated.h"


/**
 *	UWHReplicatedSubsystem
 *	@brief A WorldSubsystem that replicates over network
 */
UCLASS(Abstract, ClassGroup=(WH), Category="Core")
class WH_CORE_API UWHReplicatedSubsystem : public UWorldSubsystem,	public FTickableGameObject
{
	GENERATED_BODY()

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** called every frame */
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;

	/**  the replication function, called via @see ReplicationComponent and GameState */
 	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

private:

	/** The component we track for replication */
	UPROPERTY(Transient)
	class UWHReplicatedSubsystemComponent* ReplicationComponent;

};
