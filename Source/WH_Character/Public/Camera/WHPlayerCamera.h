/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "WHPlayerCamera.generated.h"

/**
 *	@class AWHCharacterBase
 *	Character base class, handle animation and actions
 */
UCLASS(Abstract, Blueprintable, ClassGroup=(WH), Category = "Wicked Havens|Character")
class WH_CHARACTER_API AWHPlayerCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AWHPlayerCamera(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// <ACameraActor overrides>
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// <\ACameraActor overrides>

protected:

	/** Is the camera free (to move, rotate, zoom, ...) ? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Wicked Havens|Camera")
	bool bFreeCamera = false;

	/** Is the camera free to rotate ? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Wicked Havens|Camera")
	bool bFreeCameraRotate = false;
	
private:	
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wicked Havens|Camera", meta = (AllowPrivateAccess))
	class USpringArmComponent* CameraArmComponent;


};
