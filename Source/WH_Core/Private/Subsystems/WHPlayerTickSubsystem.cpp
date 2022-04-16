/* Copyright © Noé Perard-Gayot 2022. */

#include "Subsystems/WHPlayerTickSubsystem.h"

bool UWHPlayerTickSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if(GetClass()->HasAnyClassFlags(CLASS_Abstract)) // do not spawn if abstract :)
		return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void UWHPlayerTickSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	bInitialized = true;
}

void UWHPlayerTickSubsystem::Deinitialize()
{
	bInitialized = false;
	Super::Deinitialize();
}

void UWHPlayerTickSubsystem::Tick(float DeltaTime)
{
}

TStatId UWHPlayerTickSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWHPlayerTickSubsystem, STATGROUP_Tickables);
}

