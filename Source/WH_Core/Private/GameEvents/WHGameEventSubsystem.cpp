/* Copyright © Noé Perard-Gayot 2022. */

#include "GameEvents/WHGameEventSubsystem.h"
#include "Net/UnrealNetwork.h"

void UWHGameEventSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UWHGameEventSubsystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHGameEventSubsystem, RegisteredEvents);
}

void UWHGameEventSubsystem::RegisterGameEvent(UWHGameEvent* GameEvent)
{
	RegisteredEvents.Add(GameEvent);
}

void UWHGameEventSubsystem::UnregisterGameEvent(UWHGameEvent* GameEvent)
{
	RegisteredEvents.Remove(GameEvent);
}
