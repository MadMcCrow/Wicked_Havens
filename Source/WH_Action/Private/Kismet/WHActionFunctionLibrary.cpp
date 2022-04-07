/* Copyright © Noé Perard-Gayot 2022. */

#include "Kismet/WHActionFunctionLibrary.h"

#include "System/WHActionSubsystem.h"
#include "WH_Action/WH_Action.h"

void UWHActionFunctionLibrary::ChangeInputContext(APlayerController* PlayerController, const UInputMappingContext* MappingContext)
{
	// TODO:
}

void UWHActionFunctionLibrary::AddAction(APlayerController* PlayerController, UWHActionBase* InAction)
{
	if (auto Subsystem = GetPlayerActionSubsystem(PlayerController))
	{
		Subsystem->AddAction(InAction);
	}
}

void UWHActionFunctionLibrary::RemoveAction(APlayerController* PlayerController, UWHActionBase* InAction)
{
	if (auto Subsystem = GetPlayerActionSubsystem(PlayerController))
	{
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
		UE_LOG(LogWHAction, Warning, TEXT("Tried to get Local Player of Remote Player %s"), *PlayerController->GetName());
	}
	return {};
}
