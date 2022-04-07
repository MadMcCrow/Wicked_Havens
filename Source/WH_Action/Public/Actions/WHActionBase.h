/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "WHActionBase.generated.h"

// Forward declaration
class UInputAction;
class APawn;

/**
 *	@class UWHActionBase
 *	What to do on an input
 *	@note  Derive this to control UI, Characters, etc ...
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew, ClassGroup=(WH), Category = "Wicked Havens|Action", HideCategories="Object")
class WH_ACTION_API UWHActionBase : public UObject
{
	GENERATED_BODY()
	friend class UWHActionSubsystem;

public:
	
	UWHActionBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** defined enhanced input to auto trigger */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action|Enhanced Input")
	TObjectPtr<UInputAction> InputAction;

	/** Trigger event to bind to */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action|Enhanced Input")
	ETriggerEvent TriggerEvent;
	
protected:
	
	/**
	 *	@event OnInputAction
	 *	Event called on Input. implement your action here.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void OnInputAction(const FInputActionInstance& ActionInstance);
	virtual void OnInputAction_Implementation(const FInputActionInstance& ActionInstance);
	
	/**
	 *	@func GetActionController
	 *	get the controller that originated that action
	 *	@todo When TObjectPtr will be supported by BP, move to it
	 */
	UFUNCTION(BlueprintPure, Category="Action")
	APlayerController* GetActionController() const;

	/**
	 *	@func GetControlledPawn
	 *	get the pawn controlled by controller returned by @see GetActionController
	 */
	UFUNCTION(BlueprintPure, Category="Action")
	APawn* GetControlledPawn() const;

private:

	/**
	 *	Cached player controller
	 *	Maybe we should use some kind of weak pointer
	 */
	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<APlayerController> ActionPlayerController;
	
	FORCEINLINE bool IsValidAction() const {return !InputAction.IsNull(); }

};
