// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/WHFightComponent.h"

// Sets default values for this component's properties
UWHFightComponent::UWHFightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWHFightComponent::IsInRange(const AActor* Target) const
{
	return false;
}