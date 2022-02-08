/* Copyright © Noé Perard-Gayot 2021. */

#include "WHGameEvent.h"
#include "Net/UnrealNetwork.h"

// CTR
AWHGameEvent::AWHGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{
}

void AWHGameEvent::LaunchEvent(AActor * Source, AActor* Target)
{
	if (CanRunEvent())
	{
		// ask to run on server (will also perform a check)
		Net_RequestEventStart(Source, Target);
	}
}


void AWHGameEvent::StopEvent(bool bEndSuccess)
{
	if (CanStopEvent())
	{
		// ask to run on server (will also perform a check)
		Net_RequestEventStop(bEndSuccess);
	}
}

bool AWHGameEvent::CanRunEvent_Implementation() const
{
	return true;
}

void AWHGameEvent::BeginEvent_Implementation()
{
	// default event does nothing
}

void AWHGameEvent::EndEvent_Implementation(bool bEndSuccess)
{
	// default event does nothing
}

AActor* AWHGameEvent::GetSource() const
{
	return SourceActor;
}

AActor* AWHGameEvent::GetTarget() const
{
	return TargetActor;
}

void AWHGameEvent::Net_RequestEventStart_Implementation(AActor * Source, AActor* Target)
{
	if (CanRunEvent())
	{
		SourceActor = Source;
		TargetActor = Target;
		Net_PlayEvent();
	}
}

void AWHGameEvent::Net_RequestEventStop_Implementation(bool bEndSuccess)
{
	if (CanStopEvent())
	{
		Net_EndEvent(bEndSuccess);
	}
}

void AWHGameEvent::Net_PlayEvent_Implementation()
{
	// play event;
	BeginEvent();
}

void AWHGameEvent::Net_EndEvent_Implementation(bool bEndSuccess)
{
	EndEvent(bEndSuccess);
}

void AWHGameEvent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWHGameEvent, SourceActor);
	DOREPLIFETIME(AWHGameEvent, TargetActor);
}
