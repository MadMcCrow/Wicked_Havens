/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "WHCharacterAction.generated.h"


/**
 *	@class UWHCharacterAction
 *	What to do on an Action (input or other)
 *	@todo
 *		- maybe make this a ActorComponent
 *		- Set what animation state or whatever to play
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew, ClassGroup=(WH), Category = "Wicked Havens|Character")
class UWHCharacterAction : public UObject
{
	GENERATED_BODY()
	friend class AWHCharacterBase;

public:
	
	UWHCharacterAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** defined enhanced input to auto trigger */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action|Enhanced Input")
	TObjectPtr<UInputAction> InputAction;

	/** Trigger event to bind to */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action|Enhanced Input")
	ETriggerEvent TriggerEvent;

	/**
	 *	@event OnInputAction
	 *	Event called on Input. implement your action here.
	 *	@todo : maybe change to an event that have the character as a parameter
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void OnInputAction(const FInputActionInstance& ActionInstance);
	virtual void OnInputAction_Implementation(const FInputActionInstance& ActionInstance);

	/**
	 *	@func GetActingCharacter
	 *	get the affected character.
	 *	@todo it may be simpler to store the character in a pointer and set it during bind
	 */
	UFUNCTION(BlueprintPure, Category="Action")
	AWHCharacterBase* GetActingCharacter() const;


protected:
	/** Function called by @see AWHCharacterBase, to make this work */
	virtual void BindInputAction(class UEnhancedInputComponent* InputComponent);

private:
	/** Last successful binding */
	struct FEnhancedInputActionEventBinding* EnhancedBinding;
};
