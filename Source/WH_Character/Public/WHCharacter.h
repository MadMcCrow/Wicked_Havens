/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "WHCharacter.generated.h"

// forward declaration
class UCameraComponent;
class USpringArmComponent;

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
	AWHCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// <ACharacter overrides>
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	// <\ACharacter overrides>

protected:
	
	/** Default mapping context , will have a priority of 0 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** base move action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> DefaultMoveAction;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Function called by enhanced input on @see DefaultMoveAction */
	UFUNCTION()
	void OnMoveAction(const FInputActionInstance& ActionInstance);


public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** fast getter that cast CharacterMovement to our WH type */
	class UWHCharacterMovementComponent* GetCharacterMovementComponent() const;

	/** fast getter to know if we're aligning to movement or not */
	bool GetOrientToMovement() const;

	/**
	*	LookAt
	*	@param Target	what should we aim toward
	*	this is only meant for the animation.
	*/
	UFUNCTION(BlueprintCallable, Category = "Movements")
	virtual void LookAt(const FVector& Target);
};
