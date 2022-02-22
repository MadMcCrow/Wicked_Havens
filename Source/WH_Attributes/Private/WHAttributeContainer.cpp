/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeContainer.h"
#include "WHAttributeSettings.h"

FWHAttributeName::FWHAttributeName(const FName& AttributeName)
{
	if (const auto AttributeSettings = GetDefault<UWHAttributeSettings>())
	{
		EnumValue = AttributeSettings->GetValueForName(AttributeName);
	}
}

FWHAttributeName::operator FName() const
{
	if (const auto AttributeSettings = GetDefault<UWHAttributeSettings>())
	{
		return AttributeSettings->GetNameForValue(EnumValue);
	}
	return NAME_None;
}

void FWHAttribute::PostReplicatedAdd(const FWHAttributeContainer& InArraySerializer) const
{
	InArraySerializer.OnAttributeAddedDelegate.Broadcast(Name, Value);
}

void FWHAttribute::PostReplicatedChange(const FWHAttributeContainer& InArraySerializer) const
{
	InArraySerializer.OnAttributeChangedDelegate.Broadcast(Name, Value);
}

void FWHAttribute::PreReplicatedRemove(const FWHAttributeContainer& InArraySerializer) const
{
	InArraySerializer.OnAttributeRemovedDelegate.Broadcast(Name, Value);
}


bool FWHAttributeContainer::Serialize(FArchive& Ar)
{
	Ar << Attributes;
	// Should preform a few checks maybe...
	return true;
}

bool FWHAttributeContainer::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Serialize(Ar);
}

bool FWHAttributeContainer::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FastArrayDeltaSerialize<FWHAttribute>( Attributes, DeltaParms, *this );
}

void FWHAttributeContainer::InitAttributes(const TArray<FWHAttribute> InAttributes)
{
	Attributes = InAttributes;
	MarkArrayDirty();
}

void FWHAttributeContainer::AddOrChangeAttribute(const FWHAttribute& Attribute)
{
	// if there is already an element, just edit that element
	if (auto AttrPtr = Attributes.FindByPredicate([&Attribute](const FWHAttribute& AttrItr)
	{
		return AttrItr.Name == Attribute.Name;
	}))
	{
		AttrPtr->Value = Attribute.Value;
		MarkItemDirty(*AttrPtr);
		return;
	}

	// else just add :
	auto& NewAttribute = Attributes.Add_GetRef(Attribute);
	MarkItemDirty(NewAttribute);
	MarkArrayDirty();
}

bool FWHAttributeContainer::RemoveAttribute(const FWHAttributeName& AttributeName)
{
	if (Attributes.RemoveAll([&AttributeName](const FWHAttribute& AttrItr){return AttrItr.Name == AttributeName;}) > 0)
	{
		MarkArrayDirty();
		return true;
	}
	// do nothing, nothing was removed
	return false;
}

const FWHAttribute* FWHAttributeContainer::GetAttributeByName(const FWHAttributeName& AttributeName) const
{
	if (const FWHAttribute* AttrPtr = Attributes.FindByPredicate([&AttributeName](const FWHAttribute& AttrItr)
		{
			return AttrItr.Name == AttributeName;
		}))
	{
		return AttrPtr;
	}
	return nullptr;
}

FWHAttribute* FWHAttributeContainer::GetAttributeByName(const FWHAttributeName& AttributeName)
{
	if (FWHAttribute* AttrPtr = Attributes.FindByPredicate([&AttributeName](const FWHAttribute& AttrItr)
		{
			return AttrItr.Name == AttributeName;
		}))
	{
		return AttrPtr;
	}
	return nullptr;
}
