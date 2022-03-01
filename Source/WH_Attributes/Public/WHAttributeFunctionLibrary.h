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

	/**	Get the description of an attribute (for gameplay reasons)	 */
	UFUNCTION(BlueprintPure, Category="Attributes")
	static FText GetAttributeDescription();

	/**	Make and Break Functions for AttributeContainer */
	UFUNCTION(BlueprintCallable, Category="Attributes|Containers", meta = (NativeBreakFunc))
	static void BreakAttributeContainer(const FWHAttributeContainer& AttributeContainer,  TArray<FWHAttribute>& Attributes );
	UFUNCTION(BlueprintPure, Category="Attributes|Containers", meta = (NativeMakeFunc))
	static void MakeAttributeContainer(const TArray<FWHAttribute>& Attributes,  FWHAttributeContainer& AttributeContainer);

	/**	Make and Break Functions for Attribute */
	UFUNCTION(BlueprintCallable, Category="Attributes", meta = (NativeBreakFunc))
	static void BreakAttribute(const FWHAttribute& Attribute, FWHAttributeName &FWHAttributeName, FWHAttributeValue &AttributeValue);
	UFUNCTION(BlueprintPure, Category="Attributes", meta = (NativeMakeFunc))
	static void MakeAttribute(FWHAttributeName AttributeName, FWHAttributeValue AttributeValue, FWHAttribute& Attribute);


	// Conversion Functions :
	// You can add the function you want to help you in your game

	/** Attribute Value From Float */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert Float To Attribute Value", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static FWHAttributeValue Conv_FloatToAttributeValue(float InFloat){return FWHAttributeValue(InFloat);}
	/** Float from Attribute Value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert Attribute Value To Float", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static float Conv_AttributeValueToFloat(const FWHAttributeValue& InAttribute){return InAttribute;}

	/** Attribute Value From String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert String To Attribute Value", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static FWHAttributeValue Conv_StringToAttributeValue(FString InString){return FWHAttributeValue(InString);}
	/** String from Attribute Value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert Attribute Value To Float", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static FString Conv_AttributeValueToString(const FWHAttributeValue& InAttribute){return InAttribute;}

	/** Attribute Value From Int */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert Int To Attribute Value", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static FWHAttributeValue Conv_IntToAttributeValue(int InInt){return FWHAttributeValue(InInt);}
	/** Int from Attribute Value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Convert Attribute Value To Int", CompactNodeTitle = "->", BlueprintAutocast, BlueprintInternalUseOnly), Category = "Attributes")
	static int Conv_AttributeValueToInt(const FWHAttributeValue& InAttribute){return InAttribute;}

};
