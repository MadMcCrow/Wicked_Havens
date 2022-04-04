/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Subsystems/WHReplicatedSubsystem.h"
#include "WHGameEventSubsystem.generated.h"


// forward declaration
class UWHGameEvent;

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|GameEvent")
class WH_GAMEEVENT_API UWHGameEventSubsystem : public UWHReplicatedSubsystem
{
	GENERATED_BODY()

public:

	// --- Begin UWHReplicatedSubsystem Interface ---
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// --- End UWHReplicatedSubsystem Interface ---

	void RegisterGameEvent(UWHGameEvent* GameEvent);
	void UnregisterGameEvent(UWHGameEvent* GameEvent);

private:

	UPROPERTY(Replicated)
	TArray<UWHGameEvent*> RegisteredEvents;

};
