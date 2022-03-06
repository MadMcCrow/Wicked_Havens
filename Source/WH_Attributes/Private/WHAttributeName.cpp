/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeName.h"
#include "WHAttributeSubsystem.h"

// simply stored in a static value
const FName NameNone = NAME_None;
const FWHAttributeName InvalidDefault = FWHAttributeName();


FWHAttributeName::FWHAttributeName()
{
	// BAD!
}

FWHAttributeName::FWHAttributeName(const FName& AttributeName)
{
	UniqueID	= UWHAttributeSubsystem::GetIDForName(AttributeName);
}


FWHAttributeName::FWHAttributeName(const FWHAttributeName& InAttribute)
{
	UniqueID	= InAttribute.UniqueID;
}

FWHAttributeName& FWHAttributeName::operator=(const FWHAttributeName& Other)
{
	UniqueID	= Other.UniqueID;
	return *this;
}

const FName& FWHAttributeName::GetName() const
{
	return UWHAttributeSubsystem::GetNameForID(UniqueID);
}

bool FWHAttributeName::IsValid() const
{
	return GetName() != NAME_None;
}

FString FWHAttributeName::ExportIDString() const
{
	FString Result;
	static const FGuid DefaultValue;
	const auto IDName = GET_MEMBER_NAME_CHECKED(FWHAttributeName, UniqueID);
	const auto Property = FindFProperty<FProperty>(FWHAttributeName::StaticStruct(), *IDName.ToString(), EFieldIterationFlags::None);
	Property->ExportTextItem(Result, &UniqueID, &DefaultValue , nullptr, 0);
	return Result;
}


FString FWHAttributeName::Export(const FWHAttributeName& Name)
{
	FString ExportString;
	StaticStruct()->ExportText(ExportString, &Name, &InvalidDefault, nullptr, 0, nullptr, true);
	return ExportString;
}

FWHAttributeName FWHAttributeName::Import(const FString& String)
{
	FWHAttributeName NewEditedName;
	StaticStruct()->ImportText(*String, &NewEditedName, nullptr, 0,GLog, TEXT("FWHAttributeName"), true);
	return NewEditedName;
}
