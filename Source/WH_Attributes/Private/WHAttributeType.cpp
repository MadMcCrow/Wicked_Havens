/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeType.h"
#if WITH_EDITOR
#include "EdGraphSchema_K2.h"
#endif // WITH_EDITOR

TOptional<FString> FWHAttributeType::GetArrayBaseType() const
{
	if(IsArrayType())
	{
		return CPPType.RightChop(7).LeftChop(1);
	}
	return TOptional<FString>();
}

bool FWHAttributeType::IsArrayType() const
{
	return CPPType.StartsWith(TEXT("TArray<"));
}

FString FWHAttributeType::Export(const FWHAttributeType& Name, FWHAttributeType DefaultValue)
{
	FString ExportString;
	StaticStruct()->ExportText(ExportString, &Name, &DefaultValue, nullptr, 0, nullptr, true);
	return ExportString;
}

FWHAttributeType FWHAttributeType::Import(const FString& String)
{
	{
		FWHAttributeType NewEditedName;
		StaticStruct()->ImportText(*String, &NewEditedName, nullptr, 0,GLog, TEXT("FWHAttributeType"), true);
		return NewEditedName;
	}
}
