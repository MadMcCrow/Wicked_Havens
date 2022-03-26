/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttribute.h"

FWHAttributeRef::FWHAttributeRef(const UWHAttributeBase* AttributeObject)
{
	if (AttributeObject)
		Path= AttributeObject->GetClass();
}

void UWHAttributeBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	// if you have custom values to serialize, do it there.
}
