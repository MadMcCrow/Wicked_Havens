/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHCombatFunctionLibrary.generated.h"


/**
 *	@class UWHCombatFunctionLibrary
 *	a collection of functions to help you find your target and kill them
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|Combat", Meta = (DisplayName="Combat Library"))
class WICKED_HAVENS_API UWHCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 *	Find target function
	 *	@todo: replace character by targeting component
	 */
	UFUNCTION(BlueprintCallable, Category="Combat|Targeting")
	static bool FindCombatTarget(class AWHCharacter* Character, class AActor* OutTarget, bool& OutbInRange, bool& bIsEnemy);

};

