/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WHGameEventSubsystem.generated.h"

/**
 * @brief Component for GameState that will be owned by UWHGameEventSubsystem to enable it's replication
 * UWHGameEventSubsystemComponent
 */
UCLASS(ClassGroup=(WH), Category="GameEvent")
class WH_GAMEEVENT_API UWHGameEventSubsystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual bool GetComponentClassCanReplicate() const {return true;}
 	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
 	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
};


/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="GameEvent")
class WH_GAMEEVENT_API UWHGameEventSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override; 
 	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
 	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

private:

	UPROPERTY(Transient)
	UWHGameEventSubsystemComponent* ReplicationComponent;

};
