/* Copyright © Noé Perard-Gayot 2022. */

#include "System/WHActionSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "../../../../../UnrealEngine/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemStats.h"
#include "Kismet/GameplayStatics.h"
#include "System/WHActionSettings.h"
#include "WH_Action/WH_Action.h"

void UWHActionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// make sure that Enhanced Input is already initialized
	Collection.InitializeDependency<UEnhancedInputLocalPlayerSubsystem>();
	const auto Settings = GetDefault<UWHActionSettings>();
	const auto Mapping = Settings ? TSoftObjectPtr<UInputMappingContext>(Settings->DefaultMappingContext) : nullptr;
	SetupInputMapping(Mapping);
}

void UWHActionSubsystem::Deinitialize()
{
	// remove all actions : 
	while(ActionBindings.IsValidIndex(0))
	{
		RemoveAction(ActionBindings[0].Action);
	}
	
	// remove input component
	if (const auto PlayerController = GetLocalPlayer()->GetPlayerController(GetWorld()))
	{
		PlayerController->PopInputComponent(InputComponent);
	}
	InputComponent = nullptr;
	InputController = nullptr;
	// finish deinit
	Super::Deinitialize();
}


void UWHActionSubsystem::AddAction(const TObjectPtr<UWHActionBase>& InAction)
{
	if (UNLIKELY(!InputComponent))
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogWHAction, Error, TEXT("Cannot add Action %s, no Input Component found"), *InAction->GetName());
#endif // !UE_Build_SHIPPING
		return;
	}

	// remove any pre-existing action binding
	RemoveAction(InAction);
	if (InAction->IsValidAction())
	{
		FWHActionBinding& BindingRef = ActionBindings.Add_GetRef(InAction);
		BindingRef.Binding.Reset(&InputComponent->BindAction(InAction->InputAction, InAction->TriggerEvent, InAction, GET_FUNCTION_NAME_CHECKED(UWHActionBase,OnInputAction)));
		InAction->ActionPlayer = GetLocalPlayer();
	}
	

}

void UWHActionSubsystem::RemoveAction(const TObjectPtr<UWHActionBase>& InAction)
{
	if (UNLIKELY(!InputComponent))
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogWHAction, Error, TEXT("Cannot remove Action %s, no Input Component found"), *InAction->GetName());
#endif // !UE_Build_SHIPPING
		return;
	}

	if (FWHActionBinding* FoundBinding = ActionBindings.FindByPredicate([InAction](const FWHActionBinding& PredItr)
	{
		return PredItr.Action == InAction;
	}))
	{
		if(FoundBinding->Binding.IsValid())
		{
			InputComponent->RemoveBinding(*FoundBinding->Binding.Release());
		}
		ActionBindings.Remove(*FoundBinding);
	}
}

bool UWHActionSubsystem::SetupInputComponent(const TObjectPtr<APlayerController>& Controller)
{
	if (!GetWorld())
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogWHAction, Error, TEXT("Could not find a valid world to create InputComponent"));
#endif // !UE_Build_SHIPPING
		return false;
	}
	
	if (!InputComponent)
	{
		const auto Settings = GetDefault<UWHActionSettings>();
		InputComponent = NewObject<UEnhancedInputComponent>(this, Settings->InputComponentClass.TryLoadClass<UEnhancedInputComponent>());
		InputComponent->RegisterComponentWithWorld(GetWorld());
		InputComponent->bBlockInput = Settings->InputBlocking; 
		InputComponent->Priority	= Settings->InputPriority;
	}
	
	if (!Controller || Controller != InputController)
	{
		if (InputController)
		{
			InputController->PopInputComponent(InputComponent);
			InputController = nullptr;
		}
		if (Controller)
		{
			Controller->PushInputComponent(InputComponent);
			InputController = Controller;
			return true;
		}
	}
	return false;
}

bool UWHActionSubsystem::SetupInputMapping(const TSoftObjectPtr<UInputMappingContext>& MappingContext)
{
	// we need settings to proceed;
	if (const auto Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (auto Mapping = MappingContext.LoadSynchronous())
		{
			// Remove possibly previously added context
			Subsystem->RemoveMappingContext(Mapping);
			// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
			Subsystem->AddMappingContext(Mapping, 0);
			return true;
		}
	}
	return false;
}

