/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WHTargetableInterface.generated.h"

/**
 *	@interface UWHTargetableInterface
 *	Interface to add the ability to be a target to an object.
 */
UINTERFACE(BlueprintType, Category="Wicked Havens|Combat")
class WICKED_HAVENS_API UWHTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

class WICKED_HAVENS_API IWHTargetableInterface
{
	GENERATED_BODY()
};