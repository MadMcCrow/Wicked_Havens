/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "WHActionBase.generated.h"

// Forward declaration
class UInputAction;
class APawn;
class UEnhancedInputComponent;

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
	 *	get the controller associated with this action
	 */
	UFUNCTION(BlueprintPure, Category="Action", meta=(WorldContext = "WorldContextObject"))
	APlayerController* GetActionController(const UObject* WorldContextObject = nullptr) const;

	/**
	 *	@func GetControlledPawn
	 *	get the pawn controlled by controller returned by @see GetActionController
	 *	TODO : Move to Character Actions
	 */
	UFUNCTION(BlueprintPure, Category="Action", meta=(WorldContext = "WorldContextObject"))
	APawn* GetControlledPawn(const UObject* WorldContextObject = nullptr) const;

private:

	/**
	 *	Cached player controller
	 *	Maybe we should use some kind of weak pointer
	 */
	TObjectPtr<ULocalPlayer> ActionPlayer;
	
	FORCEINLINE bool IsValidAction() const {return !InputAction.IsNull(); }

};
