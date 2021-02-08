// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/WHPlayerControllerBase.h"
#include "Player/WHPlayerInput.h"

AWHPlayerControllerBase::AWHPlayerControllerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AWHPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AWHPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

bool AWHPlayerControllerBase::ActionWasDoubleClicked(FName ActionName) const
{
	bool bWasDoubledClicked = false;
	if (UWHPlayerInput* Input = Cast<UWHPlayerInput>(PlayerInput))
	{
		const TArray<FInputActionKeyMapping> KeyMaps = Input->GetKeysForAction(ActionName);
		for (const FInputActionKeyMapping& KeyMap : KeyMaps)
		{
			return KeyWasDoubleClicked(KeyMap.Key);
		}
	}
	return bWasDoubledClicked;
}

bool AWHPlayerControllerBase::KeyWasDoubleClicked(FKey KeyInput) const
{
	if (UWHPlayerInput* Input = Cast<UWHPlayerInput>(PlayerInput))
	{
		if (Input->WasKeyDoubleClicked(KeyInput))
			return true;
	}
	return false;
}

bool AWHPlayerControllerBase::IsUsingGamepad() const
{
	if (UWHPlayerInput * Input = Cast<UWHPlayerInput>(PlayerInput))
	{
		return Input->IsGamepad();
	}
	return false;
}

void AWHPlayerControllerBase::GetCursorWorldTarget(FVector& OutVector, AActor *&OutActor) const
{
	FHitResult RayResult;
	if(	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, RayResult))
	{
		OutVector = RayResult.ImpactPoint;
		OutActor  = RayResult.GetActor();
		return;
	}
	OutVector = GetPawn()->GetActorLocation();
	OutActor = nullptr;
}
