/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSettings.h"

UEnum* UWHAttributeSettings::GetAttributeEnum() const
{
	return Cast<UEnum>(AttributesEnum.TryLoad());
}

int64 UWHAttributeSettings::GetValueForName(const FName& InName) const
{
	if (const auto Enum = GetAttributeEnum())
	{
		return Enum->GetValueByName(InName, EGetByNameFlags::ErrorIfNotFound | EGetByNameFlags::CheckAuthoredName);
	}
	return INDEX_NONE;
}

FName UWHAttributeSettings::GetNameForValue(const int64& InValue) const
{
	if (const auto Enum = GetAttributeEnum())
	{
		return Enum->GetNameByValue(InValue);
	}
	return NAME_None;
}
