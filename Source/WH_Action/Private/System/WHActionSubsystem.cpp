/* Copyright © Noé Perard-Gayot 2022. */

#include "System/WHActionSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "System/WHActionSettings.h"
#include "WH_Action/WH_Action.h"

void UWHActionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// make sure that Enhanced Input is already initialized
	Collection.InitializeDependency<UEnhancedInputLocalPlayerSubsystem>();

	// Get our infos
	const auto Settings = GetDefault<UWHActionSettings>();
	const auto PlayerController = GetPlayerController();

	// if one of them is not found, we cannot proceed
	if (!Settings || PlayerController.IsNull())
	{
		UE_LOG(LogWHAction, Error, TEXT("Could not initialized Action Subsystem"))
		return;
	}

	// Setup default input mapping
	if (const auto Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		// TODO: make Mapping loading async
		const auto Mapping = Cast<UInputMappingContext>(Settings->DefaultMappingContext.TryLoad());
		// Remove possibly previously added context
		Subsystem->RemoveMappingContext(Mapping);
		// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
		Subsystem->AddMappingContext(Mapping, 0);
	}
	
	// If it doesn't exist create it and bind delegates
	if (InputComponent.IsNull())
	{
		InputComponent = NewObject<UEnhancedInputComponent>(this, Settings->InputComponentClass.TryLoadClass<UEnhancedInputComponent>());
		InputComponent->RegisterComponent();
		InputComponent->bBlockInput = Settings->InputBlocking; 
		InputComponent->Priority	= Settings->InputPriority;
	}
	else
	{
		// Make sure we only have one instance of the InputComponent on the stack
		PlayerController->PopInputComponent(InputComponent);
	}
	PlayerController->PushInputComponent(InputComponent);
}

void UWHActionSubsystem::Deinitialize()
{
	const auto PlayerController = GetPlayerController();
	if (PlayerController.IsNull())
	{
		UE_LOG(LogWHAction, Error, TEXT("Could not deinitialize Action Subsystem"))
		return;
	}

	// remove all actions : 
	while(ActionBindings.IsValidIndex(0))
	{
		RemoveAction(ActionBindings[0].Action);
	}

	// remove input component
	PlayerController->PopInputComponent(InputComponent);

	// finish deinit
	Super::Deinitialize();
}


void UWHActionSubsystem::AddAction(const TObjectPtr<UWHActionBase>& InAction)
{
	if (InAction.IsNull() || InputComponent.IsNull())
		return;

	// remove any pre-existing action binding
	RemoveAction(InAction);
	if (InAction->IsValidAction())
	{
		FWHActionBinding& BindingRef = ActionBindings.Add_GetRef(InAction);
		BindingRef.Binding.Reset(&InputComponent->BindAction(InAction->InputAction, InAction->TriggerEvent, InAction, GET_FUNCTION_NAME_CHECKED(UWHActionBase,OnInputAction)));
		InAction->ActionPlayerController = GetPlayerController();
	}
}

void UWHActionSubsystem::RemoveAction(const TObjectPtr<UWHActionBase>& InAction)
{
	if (InputComponent.IsNull())
		return;
	
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

TObjectPtr<APlayerController> UWHActionSubsystem::GetPlayerController() const
{
	const auto Player = GetLocalPlayer<ULocalPlayer>();
	const auto World = GetWorld();
	return Player->GetPlayerController(World);
}
