/* Copyright © Noé Perard-Gayot 2022. */

#include "Subsystems/WHReplicatedSubsystem.h"

#include "GameFramework/GameStateBase.h"
#include "Subsystems/WHReplicatedSubsystemComponent.h"

bool UWHReplicatedSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if(GetClass()->HasAnyClassFlags(CLASS_Abstract)) // do not spawn if abstract :)
		return false;
	return Super::ShouldCreateSubsystem(Outer);
}

void UWHReplicatedSubsystem::Tick(float DeltaTime)
{
	if (ReplicationComponent == nullptr || ReplicationComponent->IsBeingDestroyed())
	{
		/** World may stranglely, not exist */
		if (auto World = GetWorld())
		{
			if(const auto GameState = World->GetGameState())
			{
				const auto Comp = GameState->AddComponentByClass(UWHReplicatedSubsystemComponent::StaticClass(), false, FTransform(), false);
				ReplicationComponent = Cast<UWHReplicatedSubsystemComponent>(Comp);
			}
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
