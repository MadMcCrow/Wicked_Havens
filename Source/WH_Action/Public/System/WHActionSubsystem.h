/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Actions/WHActionBase.h"
#include "EnhancedInputComponent.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WHActionSubsystem.generated.h"

// forward declaration
class APlayerController;
struct FEnhancedInputActionEventBinding;


USTRUCT()
struct FWHActionBinding
{
	GENERATED_BODY()

	/** Could be turned into a Shared or Weak pointer to avoid errors */
	UPROPERTY()
	TObjectPtr<UWHActionBase> Action;
	
	TUniquePtr<FEnhancedInputActionEventBinding> Binding;

	//CTR
	FWHActionBinding() = default;

	FWHActionBinding(const TObjectPtr<UWHActionBase>& InAction) : Action(InAction)
	{}
	// Copy CTR and operator only copies the action (required because of TUniquePtr deletion)
	FWHActionBinding(const FWHActionBinding& Other) : Action(Other.Action){}
	FWHActionBinding& operator=(const FWHActionBinding& Other) {Action = Other.Action; return *this;}

	
	// equal operator is required for array operations : (no need to check binding, it cannot be the same because UniquePtr)
	bool operator==(const FWHActionBinding& Other) const {return Action == Other.Action;}
	
};

/**
 *	@class UWHActionSubsystem
 *	@brief	Subsystem registering Actions and binding them to inputs.
 *	Acts as a SPoE for Action Module (via Function Library)
 */
UCLASS(ClassGroup=(WH), Category = "Wicked Havens|Action", MinimalAPI)
class UWHActionSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:

	// <ULocalPlayerSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// <\ULocalPlayerSubsystem-API>

	/** Add an action to the stack : bind it to current context */
	void AddAction(const TObjectPtr<UWHActionBase>& InAction);

	/** remove an action from the stack, unbinds it */
	void RemoveAction(const TObjectPtr<UWHActionBase>& InAction);

	
private:

	/**
	 *	The actions active for the local player
	 */
	UPROPERTY(Transient)
	TArray<FWHActionBinding> ActionBindings;

	/** The input component that will handle our inputs */
	UPROPERTY(Transient)
	TObjectPtr<UEnhancedInputComponent> InputComponent;

	/** Get the player controller out of the */
	TObjectPtr<APlayerController> GetPlayerController() const;
};


