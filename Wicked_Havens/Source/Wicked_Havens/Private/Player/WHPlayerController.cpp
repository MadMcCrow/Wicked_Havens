// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WHPlayerController.h"
#include "Player/Components/WHPathComponent.h"
#include "Player/Components/WHPlayerAIComponent.h"

FName AWHPlayerController::PathComponentName = FName("PathComponent");
FName AWHPlayerController::AIComponentName = FName("AIComponent");


AWHPlayerController::AWHPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Creat eour components
	PathComponent = ObjectInitializer.CreateDefaultSubobject<UWHPathComponent>(this, PathComponentName);
	AIComponent   = ObjectInitializer.CreateDefaultSubobject<UWHPlayerAIComponent>(this, AIComponentName);
	// Set Input default name
	SetDestinationActionName = FName("SetDestination");
	SetDestinationActionMode = EInputEvent::IE_Released;
}

void AWHPlayerController::SetupInputComponent()
{
		Super::SetupInputComponent();
		InputComponent->BindAction(SetDestinationActionName, SetDestinationActionMode, this, &AWHPlayerController::SetDestination);
}

void AWHPlayerController::SetDestination()
{
	if (PathComponent && AIComponent)
	{
		PathComponent->SetDestination();
		AIComponent->SetDestination();
	}
}
