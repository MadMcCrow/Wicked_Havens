/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeName.h"
#include "WHAttributeSettings.h"

FWHAttributeName::FWHAttributeName()
{
	// BAD!
}

FWHAttributeName::FWHAttributeName(const FName& AttributeName)
{
	if (const auto AttributeSettings = GetDefault<UWHAttributeSettings>())
	{
		UniqueID = AttributeSettings->GetIDForName(AttributeName);
	}
}

FWHAttributeName::FWHAttributeName(const FWHAttributeName& InAttribute)
{
	Name		= InAttribute.Name;
	UniqueID	= InAttribute.UniqueID;
}

FWHAttributeName& FWHAttributeName::operator=(const FWHAttributeName& Other)
{
	Name		= Other.Name;
	UniqueID	= Other.UniqueID;
	return *this;
}

FWHAttributeName::operator FName() const
{
	return Name; // Do checks ?
}
