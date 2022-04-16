/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Actions/WHActionBase.h"
#include "EnhancedInputComponent.h"
#include "Subsystems/WHPlayerTickSubsystem.h"
#include "WHActionSubsystem.generated.h"

// forward declaration
class APlayerController;
struct FEnhancedInputActionEventBinding;

/**
 *	A struct used for storing the various action bindings done in Wicked Havens 
 */
struct FWHActionBinding
{
	/** Action for */
	TObjectPtr<UWHActionBase> Action;

	/**
	 *	pointer to the input component binding result
	 *	We use TUniquePtr as a safety, but replacing it by a raw ptr would allow for more looseness
	 */
	TUniquePtr<FEnhancedInputActionEventBinding> Binding;

	//CTR
	FWHActionBinding() : Action(), Binding(nullptr)	{}
	FWHActionBinding(const TObjectPtr<UWHActionBase>& InAction) : Action(InAction), Binding(nullptr){}
	// == operator for Array operations (Find/Remove)
	bool operator==(const FWHActionBinding& Other) const {return Action == Other.Action;}
};

/**
 *	@class UWHActionSubsystem
 *	@brief	Subsystem registering Actions and binding them to inputs.
 *	Acts as a SPoE for Action Module (via Function Library)
 *
 *	Tick is used to make sure we have pushed our input component in
 *	the correct Player controller at all times. This may seems bad
 *	performance-wise, but there are no events triggered at the
 *	correct moment for us.
 *	We could use something like OnMatchStart, or OnWorldBeginPlay
 *	but those events are poorly documented, and may occur too late
 *	or too soon, or not at all for local multiplayer.
 *	
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Action")
class WH_ACTION_API UWHActionSubsystem : public UWHPlayerTickSubsystem
{
	GENERATED_BODY()
	
public:

	// <ULocalPlayerSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override final;
	virtual bool IsAllowedToTick() const override final;
	virtual UWorld* GetWorld() const override;
	// <\ULocalPlayerSubsystem-API>
	
	/** Add an action to the stack : bind it to current context */
	void AddAction(const TObjectPtr<UWHActionBase>& InAction);

	/** remove an action from the stack, unbinds it */
	void RemoveAction(const TObjectPtr<UWHActionBase>& InAction);


	/**
	 *	Apply input mapping to Enhanced Input Subsystem
	 *	@param InMappingContext	The mapping context you want to use
	 *	@param Priority			Higher values out-prioritize lower values.
	 */
	bool SetupInputMapping(const TObjectPtr<UInputMappingContext>& InMappingContext, int32 Priority = 0) const;
	
protected:

	/**
	 *	@func SetupInputComponent
	 *	Create (if necessary) and push input component to player controller
	 */
	bool SetupInputComponent();
	
	/** Re-Add Binding actions that were added before SetupInputComponent */
	bool BindPendingActions();


private:
	
	/**
	 *	The actions active for the local player
	 */
	TArray<FWHActionBinding> ActionBindings;
	
	/**
	 *	Actions that have been added before we had setup our inputs
	 */
	TArray<TObjectPtr<UWHActionBase>> PendingActions;

	/** The input component that will handle our inputs */
	TObjectPtr<UEnhancedInputComponent> InputComponent;

	/** The last player controller set */
	TObjectPtr<APlayerController> InputPlayerController;

	/** Simple shortcut to get player controller */
	TObjectPtr<APlayerController> GetCurrentPlayerController() const;

	/**
	 * mapping context set from settings or manually
	 * @todo : replace by array
	 */
	TObjectPtr<UInputMappingContext> MappingContext;
};


