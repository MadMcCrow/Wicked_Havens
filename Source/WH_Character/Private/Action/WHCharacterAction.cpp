/* Copyright © Noé Perard-Gayot 2022. */

#include "Action/WHCharacterAction.h"
#include "WHCharacterBase.h"

AWHCharacterBase* UWHCharacterAction::GetActingCharacter() const
{
	return Cast<AWHCharacterBase>(GetControlledPawn(this));
}

void UWHCharacterAction::AddMovementInput(const FVector& Vector)
{
	if (const auto Char = GetActingCharacter())
		Char->AddMovementInput(Vector);
}


