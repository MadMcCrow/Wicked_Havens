/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WHAnimInstance.generated.h"

class UCharacterMovementComponent;
class ACharacter;

/**
 *	Anim class for all characters and pawn in WH
 */
UCLASS()
class WH_CHARACTER_API UWHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// override
	virtual void NativeInitializeAnimation() override;

	/** Velocity vector */
	UFUNCTION(BlueprintPure, Category = "Animation|Locomotion", meta=(BlueprintThreadSafe))
	virtual FVector GetMovementVelocity() const;

	/** Velocity vector length */
	UFUNCTION(BlueprintPure, Category = "Animation|Locomotion", meta=(BlueprintThreadSafe))
	virtual float GetMovementSpeed() const;

	/** Essentially "is falling" */
	UFUNCTION(BlueprintPure, Category = "Animation|Locomotion", meta=(BlueprintThreadSafe))
	virtual bool GetIsInAir() const;

	UFUNCTION(BlueprintPure, Category = "Animation|Locomotion", meta=(BlueprintThreadSafe))
	ACharacter* GetCharacter() const;
private:

	/** Stored here for quick access */
	UPROPERTY(Transient)
	ACharacter* OwningCharacter;

	// quick cast simplification
	UCharacterMovementComponent* GetMovementComponent() const;
};
