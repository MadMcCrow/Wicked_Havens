// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WHPlayerInput.h"

bool UWHPlayerInput::InputKey(FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
{
	bLastInputIsGamepad = bGamepad;
	return Super::InputKey(Key, Event, AmountDepressed, bGamepad);
}

bool UWHPlayerInput::WasKeyDoubleClicked(FKey ClickedKey)
{
	if (FKeyState* KeyState = GetKeyStateMap().Find(ClickedKey))
	{
		return KeyState->EventAccumulator[IE_DoubleClick].Num() > 0;
	}
	return false;
}

bool UWHPlayerInput::IsGamepad() const
{
	return bLastInputIsGamepad;
}
