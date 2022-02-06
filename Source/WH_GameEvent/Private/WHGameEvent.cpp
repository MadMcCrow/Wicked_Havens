// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "GameEvent/WHGameEvent.h"

DEFINE_LOG_CATEGORY(LogWHGameEvent);

// CTR
UWHGameEvent::UWHGameEvent( const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
, bReplicatedEvent(true)
, bClientRunEvent(true)
, bServerRunEvent(true)
, bIsRunning(false)
{

}

void UWHGameEvent::StartEvent(AActor* Source, AActor* Target)
{
	if (!CanCallEvent())
	{
		return;
	}
	#if WITH_EDITOR
		UE_LOG(LogWHGameEvent, Display, TEXT("Start Event %s"), *GetName());
	#endif // WITH_EDITOR

	if (!bReplicatedEvent)
	{
		OnEventStart();
		return;
	}


	if (Source->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		// call server implementation (no need to go through networking to call ourselves)
		Net_StartServerEvent_Implementation(Source, Target);
	}
	else
	if (Source->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		// directly call Client function
		OnClientEventStart();
		// Check that we actually should allow Client to ask server for event
		if (bClientRunEvent)
		{
			// Call server event so that everyone gets the replicated event
			Net_StartServerEvent(Source, Target);
		}
	}
}

void UWHGameEvent::EndEvent(bool bEndSuccess)
{
	if (!bReplicatedEvent)
	{
		OnEventEnd();
		return;
	}

	if (GetSource()->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		if (bServerRunEvent)
		{
			Net_EndClientEvent_Implementation(bEndSuccess);
		}
		Net_EndClientEvent(bEndSuccess);
	}



}

bool UWHGameEvent::CanCallEvent_Implementation() const
{
	return true;
}

void UWHGameEvent::OnServerEventStart_Implementation()
{
}

void UWHGameEvent::OnClientEventStart_Implementation()
{
}

void UWHGameEvent::OnOwningClientEventStart_Implementation()
{
}

void UWHGameEvent::OnEventStart_Implementation()
{
}

void UWHGameEvent::OnEventEnd_Implementation()
{
}

AActor* UWHGameEvent::GetSource() const
{
	return Instigator;
}

AActor* UWHGameEvent::GetTarget() const
{
	return TargetActor;
}

bool UWHGameEvent::IsRunning() const
{
	return bIsRunning;
}

bool UWHGameEvent::IsSuccess() const
{
	return bIsSuccess;
}

void UWHGameEvent::Net_StartServerEvent_Implementation(AActor* Source, AActor* Target)
{
	Instigator	= Source;
	TargetActor	= Target;
	check(GetLocalRole() == ROLE_Authority)
	// Call events on Server
	OnServerEventStart();
	// we also are owning client
	OnOwningClientEventStart();
	// call main event if we're allowed
	if (bServerRunEvent)
	{
		OnEventStart();
	}
	// broadcast event to everyone
	Net_StartClientEvent(Source,Target); // broadcast to everyone
}

void UWHGameEvent::Net_StartClientEvent_Implementation(AActor* Source, AActor* Target)
{
	// server should have already done it's part
	if (GetLocalRole() != ROLE_Authority)
	{
		Instigator	= Source;
		TargetActor	= Target;
		OnClientEventStart();
		// if we're the owning client, call our own event
		if (GetLocalRole() == ROLE_AutonomousProxy)
		{
			OnOwningClientEventStart();
		}
		// run main event on client too
		if (bClientRunEvent)
		{
			OnEventStart();
		}
	}
}

void UWHGameEvent::Net_EndClientEvent_Implementation(bool bEndSuccess)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		bIsSuccess = bEndSuccess;
		OnEventEnd();
	}
}

ENetRole UWHGameEvent::GetLocalRole() const
{
	if (Instigator)
	{
		return Instigator->GetLocalRole();
	}
	return ROLE_None;
}

ENetRole UWHGameEvent::GetRemoteRole() const
{
	if (Instigator)
	{
		return Instigator->GetRemoteRole();
	}
	return ROLE_None;
}
