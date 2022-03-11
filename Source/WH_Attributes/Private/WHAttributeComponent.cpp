/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeComponent.h"
#include "Net/UnrealNetwork.h"

UWHAttributeComponent::UWHAttributeComponent() : Super()
{
	// TODO : Component should replicate
}


void UWHAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHAttributeComponent, Attributes);
}
