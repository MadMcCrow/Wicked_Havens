/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeComponent.h"
#include "Net/UnrealNetwork.h"

UWHAttributeComponent::UWHAttributeComponent() : Super()
{
	SetIsReplicatedByDefault(true);
}

void UWHAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHAttributeComponent, Attributes);
}
