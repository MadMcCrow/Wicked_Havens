/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHAttribute.h"
#include "WHHealth.generated.h"

/**
 *	Attribute for Health status
 *	it's then derived to get Limb health, Character Health and Object Health 
 */
UCLASS(Abstract, BlueprintType, NotBlueprintable, Category = "Wicked Havens")
class WICKED_HAVENS_API UWHHealthBase : public UWHAttributeBase
{
	GENERATED_BODY()

public:

	/** Current health */
	UFUNCTION(BlueprintPure, Category="Health")
	virtual float GetCurrentHealth() const PURE_VIRTUAL(GetCurrentHealth, return 0;)

	/** Max health */
	UFUNCTION(BlueprintPure, Category="Health")
	virtual float GetMaxHealth() const PURE_VIRTUAL(GetMaxHealth, return 0;)

	/** Remove health from attribute */
	UFUNCTION(BlueprintPure, Category="Health")
	virtual void ApplyDamage(const float& count) PURE_VIRTUAL(ApplyDamage, return;)
	
};
