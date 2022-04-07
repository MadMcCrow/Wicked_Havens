/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHActionBase.h"

UWHActionBase::UWHActionBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, TriggerEvent(ETriggerEvent::Triggered)
{
	
}

void UWHActionBase::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
	// for now do nothing

}

APlayerController* UWHActionBase::GetActionController() const
{
	return ActionPlayerController;
}

APawn* UWHActionBase::GetControlledPawn() const
{
	if (ActionPlayerController)
	{
		return ActionPlayerController->GetPawnOrSpectator();
	}
	return nullptr;
}
