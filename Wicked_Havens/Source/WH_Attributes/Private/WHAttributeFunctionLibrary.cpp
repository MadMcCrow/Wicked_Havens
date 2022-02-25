/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeFunctionLibrary.h"
#include "WHAttributeSettings.h"


FText UWHAttributeFunctionLibrary::GetAttributeDescription()
{
	return FText();
}

void UWHAttributeFunctionLibrary::BreakAttributeContainer(const FWHAttributeContainer& AttributeContainer,  TArray<FWHAttribute>& Attributes )
{
	Attributes = AttributeContainer.GetAllAttributes();
}

void UWHAttributeFunctionLibrary::MakeAttributeContainer(const TArray<FWHAttribute>& Attributes,  FWHAttributeContainer& AttributeContainer)
{
	AttributeContainer.InitAttributes(Attributes);
}

void UWHAttributeFunctionLibrary::BreakAttribute(const FWHAttribute& Attribute, FName &AttributeName, FWHAttributeValue &AttributeValue)
{
	AttributeName  = FName(Attribute.Name);
	AttributeValue = Attribute.Value;
}

void UWHAttributeFunctionLibrary::MakeAttribute(FWHAttributeName AttributeName, FWHAttributeValue AttributeValue, FWHAttribute& Attribute)
{
	Attribute = FWHAttribute(AttributeName, AttributeValue);
}
