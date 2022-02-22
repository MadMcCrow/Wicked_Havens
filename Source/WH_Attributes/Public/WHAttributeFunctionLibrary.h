/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHAttributeContainer.h"
#include "WHAttributeFunctionLibrary.generated.h"

/**
 *	UWHGameEventSubsystem
 *	@brief A replicated subsystem that will manage GameEvents
 */
UCLASS(ClassGroup=(WH), Category="Inventory")
class WH_ATTRIBUTES_API UWHAttributeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**	Get the attributes as UEnum	 */
	UFUNCTION(BlueprintPure, Category="Attributes")
	static UEnum* GetAttributeEnum();

	/**	Get the attributes as UEnum	 */
	UFUNCTION(BlueprintPure, Category="Attributes")
	static FText GetAttributeDescription();

	/**	Get the attributes as UEnum	 */
	UFUNCTION(BlueprintPure, Category="Attributes")
	static int64 GetAttributeIndex();

	/**	Make and Break Functions for AttributeContainer */
	UFUNCTION(BlueprintCallable, Category="Attributes|Containers", meta = (NativeBreakFunc))
	static void BreakAttributeContainer(const FWHAttributeContainer& AttributeContainer,  TArray<FWHAttribute>& Attributes );
	UFUNCTION(BlueprintPure, Category="Attributes|Containers", meta = (NativeMakeFunc))
	static void MakeAttributeContainer(const TArray<FWHAttribute>& Attributes,  FWHAttributeContainer& AttributeContainer);

	/**	Make and Break Functions for Attribute */
	UFUNCTION(BlueprintCallable, Category="Attributes", meta = (NativeBreakFunc))
	static void BreakAttribute(const FWHAttribute& Attribute, FName &AttributeName, FWHAttributeValue &AttributeValue);
	UFUNCTION(BlueprintPure, Category="Attributes", meta = (NativeMakeFunc))
	static void MakeAttribute(const FName &AttributeName, const FWHAttributeValue &AttributeValue, FWHAttribute& Attribute);

	/**	Get/Set Attribute as float */
	UFUNCTION(BlueprintCallable, Category="Attributes|Float")
	static void GetAttributeAsFloat(const FWHAttribute& Attribute, float &Value);
	UFUNCTION(BlueprintPure, Category="Attributes|Float")
	static void SetAttributeAsFloat(FWHAttribute& Attribute,const float &Value);


};
