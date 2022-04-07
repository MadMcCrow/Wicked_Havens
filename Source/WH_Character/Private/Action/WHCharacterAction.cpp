/* Copyright © Noé Perard-Gayot 2022. */

#include "Action/WHCharacterAction.h"
#include "WHCharacterBase.h"

UWHCharacterAction::UWHCharacterAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

AWHCharacterBase* UWHCharacterAction::GetActingCharacter() const
{
	return Cast<AWHCharacterBase>(GetControlledPawn());
}

void UWHCharacterAction::AddMovementInput(const FVector& Vector)
{
	if (const auto Char = GetActingCharacter())
	{
		Char->AddMovementInput(Vector);
	}
}


