/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WHCharacter.generated.h"

/**
 *	@class AWHCharacter
 *	Character base class, uses a lot of components
 *
 */
UCLASS(Blueprintable)
class AWHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWHCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/**
	 *	Move the character to the Right
	 *	@param Value	How much the input is. negative values will be leftward
	 *	Should be called by input events
	 */
	UFUNCTION(BlueprintCallable, Category = "Movements")
	virtual void MoveRight(float Value = 1.f);

	/**
	 *	Move the character forward
	 *	@param Value	How much the input is. negative values will be backward
	 *	Should be called by input events
	 */
	UFUNCTION(BlueprintCallable, Category = "Movements")
	virtual void MoveForward(float Value = 1.f);

	/**
	 *	Attack
	 *	@param Target	what should we aim toward
	 *	this is only meant for the animation.
	 */
	UFUNCTION(BlueprintCallable, Category = "Movements")
	virtual void LookAt(const FVector &Target);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/**
	 * make necessary calls to rotate character
	 * @todo should be moved to MovementComponent
	 */
	void Rotate(const FRotator& Rotation) const;

public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
