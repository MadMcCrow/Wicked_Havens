// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/WHAttributesComponent.h"


#include "Attributes/WHAttributesAsset.h"
#include "Engine/DemoNetDriver.h"

FWHAttributes UWHAttributesComponent::GetAttributes() const
{
    return CharacterAttributes;
}

void UWHAttributesComponent::SetAttributes(const FWHAttributes& NewAttributes)
{
	if (GetOwner()->HasAuthority())
	{
		CharacterAttributes = NewAttributes;
	}
}

void UWHAttributesComponent::OnRegister()
{
	Super::OnRegister();
	if(UWHAttributesAsset* DefaultAsset = DefaultAttributes.Get())
	{
		SetAttributes(DefaultAsset->GetAttributes());
	}
}
