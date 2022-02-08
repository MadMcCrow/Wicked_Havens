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

void UWHReplicatedSubsystem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{

}
