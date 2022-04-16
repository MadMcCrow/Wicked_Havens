/* Copyright © Noé Perard-Gayot 2022. */

#include "System/WHActionSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "System/WHActionSettings.h"
#include "WH_Action/WH_Action.h"


void UWHActionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// make sure that Enhanced Input is already initialized
	Collection.InitializeDependency<UEnhancedInputLocalPlayerSubsystem>();
	
	// Load Default Mapping
	const auto Settings = GetDefault<UWHActionSettings>();
	const auto DefaultMapping = Settings->DefaultMappingContext;
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnMappingLoadingComplete;
	OnMappingLoadingComplete.BindWeakLambda(this, [this, DefaultMapping](){MappingContext = Cast<UInputMappingContext>(DefaultMapping.TryLoad());});
	Streamable.RequestAsyncLoad(DefaultMapping,  OnMappingLoadingComplete, FStreamableManager::AsyncLoadHighPriority);

	// Make sure we are clean
	ActionBindings.Empty();
	PendingActions.Empty();
	InputPlayerController = nullptr;
	InputComponent = nullptr;
}

void UWHActionSubsystem::Deinitialize()
{
	// remove all actions : 
	for (int idx = ActionBindings.Num(); idx-->0;)
		RemoveAction(ActionBindings[idx].Action);
		
	ActionBindings.Empty();
	PendingActions.Empty();
	
	// remove input component
	if (InputPlayerController)
	{
		InputPlayerController->PopInputComponent(InputComponent);
	}
	if (InputComponent)
	{
		InputComponent->UnregisterComponent();
		InputComponent->ConditionalBeginDestroy();
	}
	InputComponent = nullptr;
	
	// Call Super
	Super::Deinitialize();
}

void UWHActionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetCurrentPlayerController())
	{

		// proceed to setup
		bool bSuccess = SetupInputMapping(MappingContext);
		bSuccess     &= SetupInputComponent();
		bSuccess     &= BindPendingActions();

		// log 
#if !UE_BUILD_SHIPPING
		UE_CLOG(!bSuccess, LogWHAction, Error,   TEXT("Action Subsystem failed to Setup"));
		UE_CLOG(bSuccess,  LogWHAction, Verbose, TEXT("Action Subsystem Sucessfully Setup for %s"), GetCurrentPlayerController()? *GetCurrentPlayerController()->GetName() : TEXT("None"));
#endif // !UE_BUILD_SHIPPING
	}
}

bool UWHActionSubsystem::IsAllowedToTick() const
{
	if (!InputPlayerController || GetCurrentPlayerController() != InputPlayerController)
		return Super::IsAllowedToTick();
	return false;
}

UWorld* UWHActionSubsystem::GetWorld() const
{
	if (const auto Player = GetLocalPlayer())
	{
		if (const auto PlayerWorld = Player->GetWorld())
			return PlayerWorld;
	}
	return Super::GetWorld();
}

void UWHActionSubsystem::AddAction(const TObjectPtr<UWHActionBase>& InAction)
{
	if (InAction)
	{
		if (!InputComponent)
		{
			PendingActions.Add(InAction);
			return;
		}
		// remove from pending if we previously added it to pendings
		PendingActions.Remove(InAction);
		//  bind
		ActionBindings.Add_GetRef(InAction).Binding.Reset(&InputComponent->BindAction(InAction->InputAction, InAction->TriggerEvent, InAction.Get(), &UWHActionBase::OnInputAction));
		InAction->ActionPlayer = GetLocalPlayer();
	}
}

void UWHActionSubsystem::RemoveAction(const TObjectPtr<UWHActionBase>& InAction)
{
	// remove potential from pending
	PendingActions.Remove(InAction);
	// Remove from actual bindings
	const auto BindingIndex = ActionBindings.FindLast(InAction);
	if (BindingIndex != INDEX_NONE && ActionBindings[BindingIndex].Binding.IsValid())
	{
		if (InputComponent)
		{
			InputComponent->RemoveBinding(*ActionBindings[BindingIndex].Binding.Release());
		}
		else
		{
			ActionBindings[BindingIndex].Binding.Release();
		}
	}
}


bool UWHActionSubsystem::SetupInputComponent()
{
	
	if (!InputComponent)
	{
		const auto Settings = GetDefault<UWHActionSettings>();
		InputComponent = NewObject<UEnhancedInputComponent>(this, Settings->InputComponentClass.TryLoadClass<UEnhancedInputComponent>());
		InputComponent->RegisterComponentWithWorld(GetWorld());
		InputComponent->bBlockInput = Settings->InputBlocking; 
		InputComponent->Priority	= Settings->InputPriority;
		return true;
	}

	if (InputComponent)
	{
		const auto Controller = GetCurrentPlayerController();
		if (InputPlayerController && Controller != InputPlayerController)
		{
			InputPlayerController->PopInputComponent(InputComponent);
		}
		if (LIKELY(Controller))
		{
			Controller->PushInputComponent(InputComponent);
		}
		InputPlayerController = Controller;
		return true;
	}
	return false;
}

bool UWHActionSubsystem::SetupInputMapping(const TObjectPtr<UInputMappingContext>& InMappingContext, int32 Priority) const
{
	// we need settings to proceed;
	if (const auto Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (UEnhancedPlayerInput* PlayerInput = Subsystem->GetPlayerInput())
		{
			if (InMappingContext)
			{
				// Remove possibly previously added context
				Subsystem->RemoveMappingContext(InMappingContext);
				// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
				Subsystem->AddMappingContext(InMappingContext, Priority);
				return true;
			}
		}
	}
#if !UE_BUILD_SHIPPING
	UE_LOG(LogWHAction, Error, TEXT("Tried to setup Input component with no Player Controller"));
#endif // !UE_BUILD_SHIPPING
	return false;
}


bool UWHActionSubsystem::BindPendingActions()
{
	ActionBindings.Reserve(ActionBindings.Num() + PendingActions.Num());
	// fix any bindings we missed
	while(PendingActions.IsValidIndex(0))
	{
		if (!PendingActions[0].IsNull())
			AddAction(PendingActions[0]);
	}
	PendingActions.Empty();
	ActionBindings.Shrink();
	return PendingActions.IsEmpty();
}


TObjectPtr<APlayerController> UWHActionSubsystem::GetCurrentPlayerController() const
{
	if (const auto Player = GetLocalPlayer())
	{
		return Player->GetPlayerController(GetWorld());
	}
	return nullptr;
}
