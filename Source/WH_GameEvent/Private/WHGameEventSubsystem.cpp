/* Copyright © Noé Perard-Gayot 2021. */

#include "WHGameEventSubsystem.h"

#include "GameFramework/GameStateBase.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

void UWHGameEventSubsystemComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    if (const auto World = GetWorld())
    {
        if (const auto GESS = World->GetSubsystem<UWHGameEventSubsystem>())
        {
            GESS->GetLifetimeReplicatedProps(OutLifetimeProps);
        }
    }
}

bool UWHGameEventSubsystemComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    Super::ReplicateSubobjects(Channel,Bunch,RepFlags);
    if (const auto World = GetWorld())
    {
          if (const auto GESS = World->GetSubsystem<UWHGameEventSubsystem>())
          {
              GESS->ReplicateSubobjects(Channel,Bunch,RepFlags);
          }
    }
}

void UWHGameEventSubsystem::Tick(float DeltaTime)
{
    if (ReplicationComponent == nullptr || ReplicationComponent->IsBeingDestroyed())
    {
        if(const auto GameState = GetWorld()->GetGameState())
        {
            const auto Comp = GameState->AddComponentByClass(UWHGameEventSubsystemComponent::StaticClass(), false, FTransform(), false);
            ReplicationComponent = Cast<UWHGameEventSubsystemComponent>(Comp);
        }
    }
}

void UWHGameEventSubsystem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool UWHGameEventSubsystem::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    return true;
}
