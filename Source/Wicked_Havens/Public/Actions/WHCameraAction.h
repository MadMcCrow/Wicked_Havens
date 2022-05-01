/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Actions/WHActionBase.h"
#include "WHCameraAction.generated.h"

class AWHPlayerCamera;

/**
 *	@class UWHCameraAction
 *	Action to control the camera
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Camera")
class UWHCameraAction : public UWHActionBase
{
	GENERATED_BODY()

public:
	/** Get Associated Character */
	UFUNCTION(BlueprintPure, Category="Action")
	AWHPlayerCamera* GetControlledCamera() const;

	/** will call add movement input on owning camera */
	virtual void AddMovementInput(const FVector& Vector);

};
