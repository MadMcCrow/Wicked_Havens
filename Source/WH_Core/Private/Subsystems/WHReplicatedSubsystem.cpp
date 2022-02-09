/* Copyright © Noé Perard-Gayot 2022. */

#include "Subsystems/WHReplicatedSubsystem.h"

#include "GameFramework/GameStateBase.h"
#include "Subsystems/WHReplicatedSubsystemComponent.h"

void UWHReplicatedSubsystem::Tick(float DeltaTime)
{
	if (ReplicationComponent == nullptr || ReplicationComponent->IsBeingDestroyed())
	{
		if(const auto GameState = GetWorld()->GetGameState())
		{
			const auto Comp = GameState->AddComponentByClass(UWHReplicatedSubsystemComponent::StaticClass(), false, FTransform(), false);
			ReplicationComponent = Cast<UWHReplicatedSubsystemComponent>(Comp);
		}
	}
}

TStatId UWHReplicatedSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWHReplicatedSubsystem, STATGROUP_Tickables);
}

void UWHReplicatedSubsystem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{

}
