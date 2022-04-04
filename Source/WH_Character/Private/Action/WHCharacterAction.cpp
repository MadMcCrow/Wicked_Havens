/* Copyright © Noé Perard-Gayot 2022. */

#include "Action/WHCharacterAction.h"
#include "EnhancedInputComponent.h"
#include "WHCharacterBase.h"

UWHCharacterAction::UWHCharacterAction(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, TriggerEvent(ETriggerEvent::Triggered)
{
	
}

void UWHCharacterAction::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
	// for now do nothing
}

AWHCharacterBase* UWHCharacterAction::GetActingCharacter() const
{
	return Cast<AWHCharacterBase>(GetOuter());
}

void UWHCharacterAction::BindInputAction(UEnhancedInputComponent* InputComponent)
{
	if (InputAction)
	{
		if (EnhancedBinding)
			InputComponent->RemoveBinding(*EnhancedBinding);
		EnhancedBinding = &(InputComponent->BindAction(	InputAction, TriggerEvent, this, &UWHCharacterAction::OnInputAction));
	}
}
