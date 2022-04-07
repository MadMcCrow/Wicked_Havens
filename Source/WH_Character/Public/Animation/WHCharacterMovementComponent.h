/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WHCharacterMovementComponent.generated.h"

/**
 *	@UWHCharacterMovementComponent
 *	Character movement component class with function helpful for Animation purposes
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Character")
class WH_CHARACTER_API UWHCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	// UCharacterMovementComponent overrides
	virtual void PerformMovement(float DeltaSeconds) override;

	/** Current angular velocity of updated component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Velocity")
	float AngularVelocity;

	/** Perform a rotation in-place */
	UFUNCTION(BlueprintCallable, Category="Movement")
	virtual void Rotate(const FRotator& Rotation);

};
