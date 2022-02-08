/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "Tickable.h"
#include "Subsystems/WorldSubsystem.h"
#include "WHGameEventSubsystem.generated.h"


/**
 *	UWHReplicatedSubsystem
 *	@brief A WorldSubsystem that replicates over network
 */
UCLASS(Abstract, ClassGroup=(WH), Category="Core")
class WH_CORE_API UWHReplicatedSubsystem : public UWorldSubsystem,	public FTickableGameObject
{
	GENERATED_BODY()

public:

	virtual void DoesSupportWorldType(EWorldType::Type WorldType) override;

	/** called every frame */
	virtual void Tick(float DeltaTime) override;

	/**  the replication function, called via @see ReplicationComponent and GameState */
 	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

private:

	/** The component we track for replication */
	UPROPERTY(Transient)
	UWHReplicatedSubsystemComponent* ReplicationComponent;

};
