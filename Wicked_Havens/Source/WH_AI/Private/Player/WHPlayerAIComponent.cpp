// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/WHPlayerAIComponent.h"
#include "Components/InputComponent.h"

UWHPlayerAIComponent::UWHPlayerAIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UWHPlayerAIComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UWHPlayerAIComponent::BindToInputComponent(UInputComponent * InputComponent)
{
	if (APlayercontroller* PC = Cast<APlayercontroller>(GetOwner())
	{
		if (UInputComponent* Input  = PC->InputComponent)
		{

		}

	}
}