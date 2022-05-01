/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHCameraActionMove.h"
#include "WHCharacterBase.h"

void UWHCameraActionMove::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
	Super::OnInputAction_Implementation(ActionInstance);
	switch(ActionInstance.GetValue().GetValueType())
	{
	default:
	case EInputActionValueType::Boolean:
		break;
	case EInputActionValueType::Axis1D:
		{
			const float InputValue = ActionInstance.GetValue().Get<float>();
			if (InputValue >= KINDA_SMALL_NUMBER)
				AddMovementInput(FVector(InputValue, 0.f,0.f));
		}
		break;
	case EInputActionValueType::Axis2D:
		{
			const FVector2D InputValue = ActionInstance.GetValue().Get<FVector2D>();
			if (!InputValue.IsNearlyZero())
				AddMovementInput(FVector(InputValue, 0.f));
		}
		break;
	case EInputActionValueType::Axis3D:
		{
			const FVector InputValue = ActionInstance.GetValue().Get<FVector>();
			if (!InputValue.IsNearlyZero())
				AddMovementInput(InputValue);	
		}
		break;
	}
}
