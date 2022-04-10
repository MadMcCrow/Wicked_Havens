/* Copyright © Noé Perard-Gayot 2022. */

#include "Kismet/WHActionFunctionLibrary.h"
#include "InputMappingContext.h"
#include "System/WHActionSubsystem.h"
#include "WH_Action/WH_Action.h"

void UWHActionFunctionLibrary::ChangeInputContext(APlayerController* PlayerController, const UInputMappingContext* MappingContext)
{
	if (const auto Subsystem = GetPlayerActionSubsystem(PlayerController))
	{
		auto ContextPath = TSoftObjectPtr<UInputMappingContext>(MappingContext);
		Subsystem->SetupInputMapping(ContextPath);
	}
}

void UWHActionFunctionLibrary::AddAction(APlayerController* PlayerController, UWHActionBase* InAction)
{
	if (const auto Subsystem = GetPlayerActionSubsystem(PlayerController))
	{
		if (Subsystem->GetActionController() != PlayerController)
		{
			Subsystem->SetupInputComponent(PlayerController);
		}
		Subsystem->AddAction(InAction);
	}
}

void UWHActionFunctionLibrary::RemoveAction(APlayerController* PlayerController, UWHActionBase* InAction)
{
	if (const auto Subsystem = GetPlayerActionSubsystem(PlayerController))
	{
		if (Subsystem->GetActionController() != PlayerController)
		{
			Subsystem->SetupInputComponent(PlayerController);
		}
		Subsystem->RemoveAction(InAction);
	}
}

UWHActionSubsystem* UWHActionFunctionLibrary::GetPlayerActionSubsystem(APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (const auto LocalPlayer = PlayerController->GetLocalPlayer())
		{
			return LocalPlayer->GetSubsystem<UWHActionSubsystem>();
		}
#if !UE_BUILD_SHIPPING
		UE_LOG(LogWHAction, Warning, TEXT("Tried to get Local Player of Remote Player %s"), *PlayerController->GetName());
#endif // !UE_BUILD_SHIPPING
	}
	return {};
}
