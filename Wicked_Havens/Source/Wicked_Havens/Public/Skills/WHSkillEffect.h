// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/WHAttributes.h"
#include "WHSkillEffect.generated.h"

UCLASS(Blueprintable)
class WICKED_HAVENS_API UWHSkillEffect : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Skill")
	FWHAttributes GetResult(const FWHAttributes &Attributes, int32 level);
	virtual FWHAttributes GetResult_Implementation(const FWHAttributes &Attributes, int32 level);

	// Helper functions:

	/**	Helps you change the Current value of an attribute */
	static FWHAttributes ChangeValue(const FWHAttributes &Attributes, EWHAttributeTypes Type, const FVariant& NewValue );

	/**	Helps you change the base value of an attribute	 */

	static FWHAttributes ChangeBaseValue(const FWHAttributes &Attributes, EWHAttributeTypes Type, const FVariant& NewBaseValue );


	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Skill")
	static FWHAttributes ChangeBaseValueInt(const FWHAttributes &Attributes, EWHAttributeTypes Type, const int& NewBaseValue )
	{
		return ChangeBaseValue(Attributes, Type, FVariant(NewBaseValue));
	}

	UFUNCTION(BlueprintPure, BlueprintCallable, Category="Skill")
	static FWHAttributes ChangeValueInt(const FWHAttributes &Attributes, EWHAttributeTypes Type, const int& NewValue )
	{
		return ChangeValue(Attributes, Type, FVariant(NewValue));
	}
};
