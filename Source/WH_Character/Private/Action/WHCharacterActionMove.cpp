/* Copyright © Noé Perard-Gayot 2022. */

#include "Action/WHCharacterActionMove.h"
#include "WHCharacterBase.h"

void UWHCharacterActionMove::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
	switch(ActionInstance.GetValue().GetValueType())
	{
	case EInputActionValueType::Boolean:
		AddMovementInput(FVector::ForwardVector);
		break;
	case EInputActionValueType::Axis1D:
		AddMovementInput(FVector(ActionInstance.GetValue().Get<float>(), 0.f, 0.f));
		break;
	case EInputActionValueType::Axis2D:
		AddMovementInput(FVector(ActionInstance.GetValue().Get<FVector2D>(), 0.f));
		break;
	case EInputActionValueType::Axis3D:
		AddMovementInput(ActionInstance.GetValue().Get<FVector>());
		break;
	}
}

void UWHCharacterActionMove::AddMovementInput(const FVector& Vector)
{
	if (const auto Char = GetActingCharacter())
	{
		Char->AddMovementInput(Vector);
	}
}
