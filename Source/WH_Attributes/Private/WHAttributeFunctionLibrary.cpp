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

void UWHAttributeFunctionLibrary::BreakAttribute(const FWHAttribute& Attribute, FWHAttributeName &AttributeName, FWHAttributeValue &AttributeValue)
{
	AttributeName  = Attribute.Name;
	AttributeValue = Attribute.Value;
}

void UWHAttributeFunctionLibrary::MakeAttribute(FWHAttributeName AttributeName, FWHAttributeValue AttributeValue, FWHAttribute& Attribute)
{
	Attribute = FWHAttribute(AttributeName, AttributeValue);
}
