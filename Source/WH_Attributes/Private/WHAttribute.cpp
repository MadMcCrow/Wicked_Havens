/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttribute.h"

FWHAttributeRef::FWHAttributeRef(const UWHAttributeBase* AttributeObject)
{
	if (AttributeObject)
		Ref= AttributeObject->GetClass();
}

FWHAttributeRef::FWHAttributeRef(const TSubclassOf<UWHAttributeBase> AttributeClass)
{
	if (AttributeClass != nullptr)
	{
		Ref = static_cast<UClass*>(AttributeClass);
	}
}

FWHAttributeRef::FWHAttributeRef(const UClass* AttributeClass)
{
	if (AttributeClass != nullptr && AttributeClass->IsChildOf<UWHAttributeBase>())
	{
		Ref = (AttributeClass);
	}
}

void UWHAttributeBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	// if you have custom values to serialize, do it there.
}

FString UWHAttributeBase::ToString_Implementation() const
{
	if (const auto Class = GetClass())
	{
		return Class->GetName();
	}
	return FString();
}
