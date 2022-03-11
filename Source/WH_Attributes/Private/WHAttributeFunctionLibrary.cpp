/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeFunctionLibrary.h"
#include "WHAttributeSubsystem.h"


bool UWHAttributeFunctionLibrary::SetAttribute_impl(FProperty* Property, void* StructPtr, FWHAttribute& Attribute)
{
	if (!Property)
		return false;

	UWHAttributeSubsystem* AttributeSubSystem = UWHAttributeSubsystem::Get();
	const auto &Type = AttributeSubSystem->GetAttributeType(Attribute.Name);

	//if (Property->GetCPPType() != Type.C)
	return false;

	TArray<uint8> Arr;
	Arr.SetNum(Property->GetSize());
	FMemory::Memcpy( Arr.GetData(), StructPtr, Property->GetSize());
	Attribute.Value = Arr;
	return true;

}
