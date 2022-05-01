/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHCharacterAction.h"
#include "WHCharacterActionMove.generated.h"


/**
 *	@class UWHCharacterActionMove
 *	Action to move your pawn around
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Character")
class UWHCharacterActionMove : public UWHCharacterAction
{
	GENERATED_BODY()

public:
	// <UWHCharacterAction-API>
	virtual void OnInputAction_Implementation(const FInputActionInstance& ActionInstance) override;
	// <\UWHCharacterAction-API>

};
