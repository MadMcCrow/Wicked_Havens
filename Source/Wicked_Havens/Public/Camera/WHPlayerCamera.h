/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "WHPlayerCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *	@class AWHPlayerCamera
 *	Class for having cameras attached to a character
 *	@todo : zoom function, rotate function, free movement function
 */
UCLASS(Blueprintable, ClassGroup=(WH), Category = "Wicked Havens|Character")
class WH_CHARACTER_API AWHPlayerCamera : public ASpectatorPawn
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
	USpringArmComponent* CameraArmComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wicked Havens|Camera", meta = (AllowPrivateAccess))
	UCameraComponent* CameraComponent;

public:

	FORCEINLINE UCameraComponent* GetCameraComponent() const {return CameraComponent;}
	FORCEINLINE USpringArmComponent* GetArmComponent() const {return CameraArmComponent;}
};
