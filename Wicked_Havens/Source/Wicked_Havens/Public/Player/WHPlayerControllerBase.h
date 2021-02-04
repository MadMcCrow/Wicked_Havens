// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WHPlayerControllerBase.generated.h"

/**
 *	Base class for Player controllers
 *	Offer functions to Deal with inputs, etc...
 */
UCLASS(ClassGroup=Player, Category = "Player")
class WICKED_HAVENS_API AWHPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	// CTR
	AWHPlayerControllerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// APlayerController overrides
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

public:

	/**
	 *	@brief will get info on FKey corresponding to ActionName to know if it was IE_DoubledClick
	 *	will need InputComponent to be a WHInputComponent
	 *	@return True if IE_DoubleClick can be found in PlayerInput
	 */
	UFUNCTION(BlueprintPure, Category= "Input")
	bool ActionWasDoubleClicked(FName ActionName) const;

	/**
	 *	@brief will get info on FKey corresponding to ActionName to know if it was IE_DoubledClick
	 *	will need InputComponent to be a WHInputComponent
	 *	@return True if IE_DoubleClick can be found in PlayerInput
	 */
	UFUNCTION(BlueprintPure, Category = "Input")
	bool KeyWasDoubleClicked(FKey KeyInput) const;

	/**
	 *	@brief ActionWasDoubleClicked will get info if last Key was on Gamepad
	 *	will need InputComponent to be a WHInputComponent
	 *	@return true for Gamepad
	 *	@todo Have more info on which gamepad (XBox, Generic, Switch, PS4/5, Steam)
	 */
	UFUNCTION(BlueprintPure, Category = "Input")
	bool IsUsingGamepad() const;

public:

	/**
	 *	@brief find what's under cursor.
	 *	Using Camera channel trace for obvious reasons
	 */
	UFUNCTION(BlueprintPure, Category = "Cursor")
	FVector GetCursorWorldLocation() const;
};

