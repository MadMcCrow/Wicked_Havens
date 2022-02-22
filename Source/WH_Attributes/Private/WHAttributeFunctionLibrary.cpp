/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeFunctionLibrary.h"
#include "WHAttributeSettings.h"

UEnum* UWHAttributeFunctionLibrary::GetAttributeEnum()
{
	if (const auto AttributeSettings = GetDefault<UWHAttributeSettings>())
	{
		return AttributeSettings->GetAttributeEnum();
	}
	return nullptr;
}

FText UWHAttributeFunctionLibrary::GetAttributeDescription()
{
	return FText();
}

int64 UWHAttributeFunctionLibrary::GetAttributeIndex()
{
	return INDEX_NONE;
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

void UWHAttributeFunctionLibrary::MakeAttribute(const FName &AttributeName, const FWHAttributeValue &AttributeValue, FWHAttribute& Attribute)
{
	Attribute = FWHAttribute({AttributeName,AttributeValue });
}

void UWHAttributeFunctionLibrary::GetAttributeAsFloat(const FWHAttribute& Attribute, float &Value)
{
	Value = Attribute.Value;
}
void UWHAttributeFunctionLibrary::SetAttributeAsFloat(FWHAttribute& Attribute, const float &Value)
{
	Attribute.Value = Value;
}
