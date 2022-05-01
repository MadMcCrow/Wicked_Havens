/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHCameraAction.h"
#include "WHCameraActionMove.generated.h"


/**
 *	@class UWHCameraActionMove
 *	Action to move your camera around
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Character")
class UWHCameraActionMove : public UWHCameraAction
{
	GENERATED_BODY()

public:
	// <UWHCharacterAction-API>
	virtual void OnInputAction_Implementation(const FInputActionInstance& ActionInstance) override;
	// <\UWHCharacterAction-API>

};
