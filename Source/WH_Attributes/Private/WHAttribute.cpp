/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttribute.h"

FWHAttributeRef::FWHAttributeRef(const UWHAttributeBase* AttributeObject)
{
	if (AttributeObject)
		Path= AttributeObject->GetClass();
}

FWHAttributeRef::FWHAttributeRef(const TSubclassOf<UWHAttributeBase> AttributeClass)
{
	if (AttributeClass != nullptr)
	{
		Path = static_cast<UClass*>(AttributeClass);
	}
}

FWHAttributeRef::FWHAttributeRef(const UClass* AttributeClass)
{
	if (AttributeClass != nullptr && AttributeClass->IsChildOf<UWHAttributeBase>())
	{
		Path = (AttributeClass);
	}
}

void UWHAttributeBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	// if you have custom values to serialize, do it there.
}
