/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHActionBase.h"
#include "WH_Action/WH_Action.h" // for log

UWHActionBase::UWHActionBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, TriggerEvent(ETriggerEvent::Triggered)
{
	
}

void UWHActionBase::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
#if !UE_BUILD_SHIPPING
	UE_LOG(LogWHAction, Display, TEXT("Action Event started "), *GetName());
#endif // !UE_Build_SHIPPING

}

APlayerController* UWHActionBase::GetActionController(const UObject* WorldContextObject) const
{
	if (ActionPlayer)
	{
		if (WorldContextObject)
		{
			return ActionPlayer->GetPlayerController(WorldContextObject->GetWorld());
		}
		return ActionPlayer->GetPlayerController(ActionPlayer->GetWorld());
	}
	return nullptr;
}

APawn* UWHActionBase::GetControlledPawn(const UObject* WorldContextObject) const
{
	if (const auto ActionPlayerController = GetActionController())
	{
		return ActionPlayerController->GetPawnOrSpectator();
	}
	return nullptr;
}
