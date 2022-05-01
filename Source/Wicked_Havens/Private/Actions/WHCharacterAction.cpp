/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHCharacterAction.h"
#include "WHCharacterBase.h"
#include "GameFramework/WHPlayerController.h"


AWHCharacterBase* UWHCharacterAction::GetActingCharacter() const
{
	if (auto WHPC = Cast<AWHPlayerController>(GetActionController()))
	{
		return WHPC->GetActiveActionCharacter();
	}
	return nullptr;
}

void UWHCharacterAction::AddMovementInput(const FVector& Vector)
{
	if (const auto Char = GetActingCharacter())
		Char->AddMovementInput(Vector);
}


