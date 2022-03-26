/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeContainer.h"
#include "WHAttributeSubsystem.h"
#include "Serialization/BufferArchive.h"

// some serialization tricks inspired by
// https://ikrima.dev/ue4guide/engine-programming/uobject-serialization/uobject-ustruct-serialization/


void FWHSerializedByte::PostReplicatedAdd(	   const FWHAttributeValue& InArraySerializer) const
{
	InArraySerializer.OnValueChange.Broadcast();
}

void FWHSerializedByte::PostReplicatedChange( const FWHAttributeValue& InArraySerializer) const
{
	InArraySerializer.OnValueChange.Broadcast();
}

void FWHSerializedByte::PreReplicatedRemove(  const FWHAttributeValue& InArraySerializer) const
{
	InArraySerializer.OnValueChange.Broadcast();
}

bool FWHAttributeValue::Serialize(FArchive& Ar)
{
	Ar << *this;
	return true;
}

bool FWHAttributeValue::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Serialize(Ar);
}

bool FWHAttributeValue::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FastArrayDeltaSerialize<FWHSerializedByte, FWHAttributeValue>( StoredValue, DeltaParms, *this );
}

bool FWHAttributeValue::Set(UWHAttributeBase* AttributeBase)
{
	auto Attribute = UWHAttributeSubsystem::GetAttributeObject(Ref);
	if (UNLIKELY(!Attribute))
		return false;

	// incorrect ref, do not set
	if (FWHAttributeRef(AttributeBase) != Ref)
		return false;

	TArray<uint8> ByteArray;
	FMemoryWriter MemoryWriter(ByteArray, true);
	MemoryWriter << AttributeBase;
	FWHSerializedByte::FromBytes(ByteArray, StoredValue);
	return true;
}

UWHAttributeBase* FWHAttributeValue::Get() const
{
	auto Attribute = UWHAttributeSubsystem::GetAttributeObject(Ref);
	if (UNLIKELY(!Attribute))
		return nullptr;

	TArray<uint8> ByteArray;
	FWHSerializedByte::ToBytes(StoredValue, ByteArray);
	FMemoryReader FromBinary = FMemoryReader(ByteArray, true);
	FromBinary.Seek(0);
	FromBinary << Attribute; // hope it's the same class as before
	FromBinary.FlushCache();
	FromBinary.Close();
	return Attribute;
}

void FWHAttributeValue::PostReplicatedAdd(const FWHAttributeContainer& InArraySerializer) const
{
	FWHAttributeValue* mutable_this = const_cast<FWHAttributeValue*>(this);
	InArraySerializer.OnAttributeAddedDelegate.Broadcast(MakeShareable(mutable_this));
}

void FWHAttributeValue::PostReplicatedChange(const FWHAttributeContainer& InArraySerializer) const
{
	FWHAttributeValue* mutable_this = const_cast<FWHAttributeValue*>(this);
	InArraySerializer.OnAttributeChangedDelegate.Broadcast(MakeShareable(mutable_this));
}

void FWHAttributeValue::PreReplicatedRemove(const FWHAttributeContainer& InArraySerializer) const
{
	FWHAttributeValue* mutable_this = const_cast<FWHAttributeValue*>(this);
	InArraySerializer.OnAttributeRemovedDelegate.Broadcast(MakeShareable(mutable_this));
}

bool FWHAttributeContainer::Serialize(FArchive& Ar)
{
	Ar << Attributes;
	return true;
}

bool FWHAttributeContainer::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Serialize(Ar);
}

bool FWHAttributeContainer::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
{
	return FastArrayDeltaSerialize<FWHAttributeValue, FWHAttributeContainer>( Attributes, DeltaParms, *this );
}
