// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "/GameFramework/SpectatorPawn.h"
#include "RTSCameraPawn.generated.h"


UCLASS(Category = "Camera")
class WH_CAMERA_API ARTSCameraPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSCameraPawn(const FObjectInitializer & ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;


protected:

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	FName InputAxisForwardName;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	FName InputAxisRightName;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	FName InputAxisZoomName;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float BaseMovementSpeed;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ZoomSpeed;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MaxZoom;

	/** Input axis for moving forward */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MinZoom;

private:

	/**
	 *	Camera Component for this pawn
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class URTSCameraComponent* CameraComponent;

	/**
	 *	Spring Arm holding the camera for this pawn
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class USpringArmComponent* CameraBoomComponent;

	/**
	 *	Movement Component for this pawn
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class URTSCameraMovementComponent* MovementComponent;

	/**
	 *	Mouse Component for this pawn
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class URTSCameraMouseComponent* MouseComponent;

public:

	static FName CameraComponentName;
	static FName MouseComponentName;
	static FName CameraBoomComponentName;


public:

	UFUNCTION(BlueprintCallable, Category = "Movemement")
	void SetFreeCamera(bool IsFree = true);


	UFUNCTION(BlueprintCallable, Category = "Movemement")
	void FollowActor(class AActor* Target);


private:

	/** Move camera to the front / back */
	UFUNCTION()
	void MoveAxisForward(float AxisValue);

	/** Move camera to the right / left */
	UFUNCTION()
	void MoveAxisRight(float AxisValue);

	/** Zoom / dezoom axis */
	UFUNCTION()
	void Zoom(float AxisValue);

	/** Move camera to the front / back */
	UFUNCTION()
	void CameraTracking();

	UFUNCTION()
	virtual float MovementSpeed() const;

private:

	/** Camera can move freely */
	UPROPERTY(Transient)
	bool bIsFreeCamera;


	/** Camera can move freely */
	UPROPERTY(Transient)
	AActor* TrackedActor;

	/** Camera can move freely */
	UPROPERTY(Transient)
	bool bIsMoveBorder;

	/** ZoomDistance defined by zoom axis */
	UPROPERTY(Transient)
	float ZoomDistance;

	/** Called by Mouse Component callback */
	UFUNCTION()
	void StartMouseMovement() { bIsMoveBorder = true; }

	/** Called by Mouse Component callback */
	UFUNCTION()
	void EndMouseMovement() { bIsMoveBorder = false; }


};
