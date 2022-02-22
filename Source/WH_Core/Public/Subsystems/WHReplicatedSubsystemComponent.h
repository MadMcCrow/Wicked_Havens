/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Components/ActorComponent.h"
#include "WHReplicatedSubsystemComponent.generated.h"

/**
 *	@class UWHReplicatedSubsystemComponent
 *	@brief component dynamically added to GameState to gain replication for a subsystem
 */
UCLASS(MinimalAPI)
class UWHReplicatedSubsystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual bool GetComponentClassCanReplicate() const override {return true;}
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
};
