/* Copyright © Noé Perard-Gayot 2022. */

#include "GameEvents/WHGameEvent.h"
#include "Net/UnrealNetwork.h"

// CTR
UWHGameEvent::UWHGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UWHGameEvent::LaunchEvent(AActor * Source, AActor* Target)
{
	if (CanRunEvent(Source,Target))
	{
		// ask to run on server (will also perform a check)
		Net_RequestEventStart(Source, Target);
	}
}


void UWHGameEvent::StopEvent(bool bEndSuccess)
{
	if (CanStopEvent())
	{
		// ask to run on server (will also perform a check)
		Net_RequestEventStop(bEndSuccess);
	}
}

bool UWHGameEvent::CanRunEvent_Implementation(AActor * Source, AActor* Target) const
{
	return true;
}

bool UWHGameEvent::CanStopEvent_Implementation() const
{
	return true;
}

void UWHGameEvent::BeginEvent_Implementation()
{
	// default event does nothing
}

void UWHGameEvent::EndEvent_Implementation(bool bEndSuccess)
{
	// default event does nothing
}

AActor* UWHGameEvent::GetSource() const
{
	return SourceActor;
}

AActor* UWHGameEvent::GetTarget() const
{
	return TargetActor;
}

void UWHGameEvent::Net_RequestEventStart_Implementation(AActor * Source, AActor* Target)
{
	if (CanRunEvent(Source,Target))
	{
		SourceActor = Source;
		TargetActor = Target;
		Net_PlayEvent();
	}
}

void UWHGameEvent::Net_RequestEventStop_Implementation(bool bEndSuccess)
{
	if (CanStopEvent())
	{
		Net_EndEvent(bEndSuccess);
	}
}

void UWHGameEvent::Net_PlayEvent_Implementation()
{
	// play event;
	BeginEvent();
}

void UWHGameEvent::Net_EndEvent_Implementation(bool bEndSuccess)
{
	EndEvent(bEndSuccess);
}

void UWHGameEvent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHGameEvent, SourceActor);
	DOREPLIFETIME(UWHGameEvent, TargetActor);
}
