// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "WHPlayerInput.generated.h"




/**
 *
 */
UCLASS()
class WICKED_HAVENS_API UWHPlayerInput : public UPlayerInput
{
	GENERATED_BODY()

public:

	virtual bool InputKey(FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad) override;


	bool WasKeyDoubleClicked(FKey ClickedKey);
	bool IsGamepad() const;

private:

	bool bLastInputIsGamepad;

};
