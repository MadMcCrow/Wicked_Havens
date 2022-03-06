/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeComponent.h"
#include "Net/UnrealNetwork.h"

UWHAttributeComponent::UWHAttributeComponent() : Super()
{
	// TODO : Component should replicate
}


FWHAttributeValue UWHAttributeComponent::GetAttributeValue(const FWHAttributeName& Name) const
{
	// TODO: make a smart implementation that will return the default value if not found
	return FWHAttributeValue();
}

void UWHAttributeComponent::SetAttributeValue(const FWHAttributeName& Name, const FWHAttributeValue& NewValue) const
{
	// TODO : Update stored values and signal replication needs
}

void UWHAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWHAttributeComponent, Attributes);
}
