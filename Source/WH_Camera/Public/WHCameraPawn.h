// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "WHCameraPawn.generated.h"

/**
 *
 */
UCLASS()
class WH_CAMERA_API AWHCameraPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	AWHCameraPawn();
	virtual void Tick(float deltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* SetupInputComponent) override;


protected:

	/** Camera Zoom Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraZoomSpeed;

	/** Camera Radius Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraDistanceMax;

	/** Camera Radius Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraDistanceMin;

	/** Camera Movement Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraMovementSpeed;

	/** Camera Scroll Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraScrollBoundary;

	/** Should the camera move? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool bCanMoveCamera;

private:

	/** Arm Component for camera offset */
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	class USpringArmComponent* ArmComponent;

	/** Arm Component for camera offset */
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	class UCameraComponent* CameraComponent;

public:

	FORCEINLINE USpringArmComponent* GetArmComponent() const  {return ArmComponent;}
	FORCEINLINE UCameraComponent* GetCameraComponent() const  {return CameraComponent;}

	/** Zooms In The Camera */
	void ZoomIn();

	/** Zooms Out The Camera */
	void ZoomOut();

	/**
	 * Moves the camera forward
	 * @param scale - (1.0 for forward, -1.0 for backward)
	 */
	void MoveCameraForward(float scale);

	/**
	 * Moves the camera forward
	 * @param scale - (1.0 for right, -1.0 for left)
	 */
	void MoveCameraRight(float scale);

};
