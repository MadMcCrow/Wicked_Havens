/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "WHCharacterBase.generated.h"

// forward declaration
class UWHCharacterAction;
/**
 *	@class AWHCharacterBase
 *	Character base class, handle animation and actions
 */
UCLASS(Abstract, Blueprintable, ClassGroup=(WH), Category = "Wicked Havens|Character")
class WH_CHARACTER_API AWHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AWHCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// <ACharacter overrides>
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// <\ACharacter overrides>


public:

	/** fast getter that cast CharacterMovement to our WH type */
	class UWHCharacterMovementComponent* GetCharacterMovementComponent() const;

	/** fast getter to know if we're aligning to movement or not */
	bool GetOrientToMovement() const;

	/**
	*	LookAt
	*	@param Target	what should we aim toward
	*	this is only meant for the animation.
	*/
	UFUNCTION(BlueprintCallable, Category = "Wicked Havens|Movement")
	virtual void LookAt(const FVector& Target);
};
