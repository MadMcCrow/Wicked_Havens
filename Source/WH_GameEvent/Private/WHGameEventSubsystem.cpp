/* Copyright © Noé Perard-Gayot 2021. */

#include "GameEvent/WHGameEventSubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"



void UWHGameEventSubsystemComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    if (auto GESS = USubsystemBlueprintLibrary::GetWorldSubsystem(this, UWHGameEventSubsystem::StaticClass()))
        GESS->GetLifetimeReplicatedProps(OutLifetimeProps);  
}

bool UWHGameEventSubsystemComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
    Super::ReplicateSubobjects(Channel,Bunch,RepFlags);
    if (auto GESS = USubsystemBlueprintLibrary::GetWorldSubsystem(this, UWHGameEventSubsystem::StaticClass()))
        GESS->ReplicateSubobjects(Channel,Bunch,RepFlags);
}

void UWHGameEventSubsystem::Tick(float DeltaTime)
{
    if (!ReplicationComponent)
    {
        if(auto GameState = GetWorld()->GetGameState())
        {
            ReplicationComponent = AddComponentByClass(UWHGameEventSubsystemComponent::StaticClass);
        }
        
    }
}

void UWHGameEventSubsystem::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool UWHGameEventSubsystem::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	Super::ReplicateSubobjects(Channel,Bunch,RepFlags);
}