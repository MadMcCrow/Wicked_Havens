/* Copyright © Noé Perard-Gayot 2022. */

#include "Actions/WHActionBase.h"

#include "EnhancedInputComponent.h"
#include "WH_Action/WH_Action.h" // for log

UWHActionBase::UWHActionBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, TriggerEvent(ETriggerEvent::Triggered)
{
}

void UWHActionBase::OnInputAction_Implementation(const FInputActionInstance& ActionInstance)
{
#if !UE_BUILD_SHIPPING
	UE_LOG(LogWHAction, Display, TEXT("Action %s : Input Action Event %s"), *GetName(), *ActionInstance.GetValue().ToString());
#endif // !UE_Build_SHIPPING

}

APlayerController* UWHActionBase::GetActionController(const UObject* WorldContextObject) const
{
	APlayerController* RetVal = nullptr;
	if (ActionPlayer)
	{
		if (WorldContextObject)
			RetVal = ActionPlayer->GetPlayerController(WorldContextObject->GetWorld());
		if (!RetVal)
			RetVal = ActionPlayer->GetPlayerController(ActionPlayer->GetWorld());
	}
#if !UE_BUILD_SHIPPING
	UE_CLOG(!RetVal, LogWHAction, Error, TEXT("Action : Could not find player controller"));
#endif // !UE_BUILD_SHIPPING
	return RetVal;
}

APawn* UWHActionBase::GetControlledPawn(const UObject* WorldContextObject) const
{
	APawn* RetVal = nullptr;
	if (const auto ActionPlayerController = GetActionController())
	{
		RetVal = ActionPlayerController->GetPawnOrSpectator();
	}
#if !UE_BUILD_SHIPPING
	UE_CLOG(!RetVal, LogWHAction, Error, TEXT("Action : Could not find player Pawn"));
#endif // !UE_BUILD_SHIPPING
	return RetVal;
}
