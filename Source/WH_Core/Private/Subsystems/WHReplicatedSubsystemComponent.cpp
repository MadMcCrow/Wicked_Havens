/* Copyright © Noé Perard-Gayot 2021. */


#include "Subsystems/WHReplicatedSubsystemComponent.h"
#include "Subsystems/WHReplicatedSubsystem.h"

void UWHReplicatedSubsystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	if (const auto World = GetWorld())
	{
		if (const auto GESS = World->GetSubsystem<UWHReplicatedSubsystem>())
		{
			GESS->GetLifetimeReplicatedProps(OutLifetimeProps);
		}
	}
}

bool UWHReplicatedSubsystemComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	return Super::ReplicateSubobjects(Channel, Bunch,RepFlags);
}
