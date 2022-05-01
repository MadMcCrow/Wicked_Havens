/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHCameraAction.h"

#include "Camera/WHPlayerCamera.h"


AWHPlayerCamera* UWHCameraAction::GetControlledCamera() const
{
	return Cast<AWHPlayerCamera>(GetActionController()->GetPawnOrSpectator());
}

void UWHCameraAction::AddMovementInput(const FVector& Vector)
{
	if (const auto Camera = GetControlledCamera())
		Camera->AddMovementInput(Vector);
}
