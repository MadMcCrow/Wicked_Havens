/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttribute.h"
#include "Engine/NetSerialization.h"
#include "WHAttributeContainer.generated.h"

// Forward declaration
struct FWHAttributeContainer;
struct FWHAttributeValue;
class UWHAttributeBase;

DECLARE_MULTICAST_DELEGATE(FWHAttributeValueDelegate)

/**
 *	@struct FWHAttributeValue
 *	Acts as a container for attribute values. we get and extract the values
 *	by applying it to a Attribute object (via serialization to Bin archive)
 *	@todo : use a BinArray serializer (should be done in WHCore)
 */
USTRUCT(BlueprintType, Category= "Attribute")
struct FWHAttributeValue : public FFastArraySerializerItem
{
	GENERATED_BODY()

	/** CTR to only set the type (and act as default CTR) */
	FWHAttributeValue(FWHAttributeRef AttributeReference = FWHAttributeRef()) :Ref(AttributeReference){}

	/**
	 *	Set
	 *	Set the Value with the attribute. return true on success
	 */
	bool Set(UWHAttributeBase* AttributeBase);

	/**
	 *	Return an Attribute that has that value
	 */
	UWHAttributeBase* Get() const;
	
	/** Holds the info about this value. */
	UPROPERTY()
	FWHAttributeRef Ref;

	/** Value changed (by at least a byte) */
	FWHAttributeValueDelegate OnValueChange;
	
private:
	
	/** Holds the serialized Attribute as binary */
	UPROPERTY()
	TArray<uint8> StoredValue;

public:

	// Begin Serialization -----
	FORCEINLINE bool Serialize(FArchive& Ar) {Ar << *this; return true;}
	FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) {return Serialize(Ar);}
	// End Serialization -----
	
	/** Called by NetSerialize of FWHAttributeContainer */
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeValue& AttributeValue )
	{
		Ar << AttributeValue.Ref;
		Ar << AttributeValue.StoredValue;
		return Ar;
	}

	// Replication Functions
	void PostReplicatedAdd(	   const FWHAttributeContainer& InArraySerializer) const;
	void PostReplicatedChange( const FWHAttributeContainer& InArraySerializer) const;
	void PreReplicatedRemove(  const FWHAttributeContainer& InArraySerializer) const;

	// Hash and comparison for map like operation
	FORCEINLINE bool operator==(const FWHAttributeValue& Other) const{return Ref == Other.Ref;}
	FORCEINLINE friend int32 GetTypeHash(const FWHAttributeValue& Value){return GetTypeHash(Value.Ref);}
};


/** Specify custom functions to look for in FWHInventory */
template<>
struct TStructOpsTypeTraits<FWHAttributeValue> : public TStructOpsTypeTraitsBase2<FWHAttributeValue>
{
	enum
	{
		WithSerializer                 = true,                         // struct has a Serialize function for serializing its state to an FArchive.
		WithNetSerializer              = true,                         // struct has a NetSerialize function for serializing its state to an FArchive used for network replication.
	};
};



/** Multicast for FWHAttributeContainer */
DECLARE_MULTICAST_DELEGATE_OneParam(FWHAttributeChangeDelegate, TSharedPtr<FWHAttributeValue>)


/**
 *	A struct to contain a list of attributes Values
 */
USTRUCT(BlueprintType, Category = "Attributes")
struct WH_ATTRIBUTES_API FWHAttributeContainer : public FFastArraySerializer
{
	GENERATED_BODY()
public:

	// Begin Serialization -----
	bool Serialize(FArchive& Ar);
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);
	// End Serialization -----

	
private:
    /** The list/Map of Attributes */
    UPROPERTY(EditAnywhere)
    TArray<FWHAttributeValue> Attributes;

	/** Retrieve attribute value that correspond to a certain attribute */
	FORCEINLINE FWHAttributeValue* FindAttributeValue(const FWHAttributeRef& Ref)
	{
		return Attributes.FindByKey(FWHAttributeValue(Ref));
	}
	/** Retrieve attribute value that correspond to a certain attribute, const version */
	FORCEINLINE const FWHAttributeValue* FindAttributeValue(const FWHAttributeRef& Ref) const
	{
		return Attributes.FindByKey(FWHAttributeValue(Ref));
	}

public:

	/** Delegate called on each changes of every attribute */
	FWHAttributeChangeDelegate OnAttributeChangedDelegate;

	/** Delegate called when an attribute is removed from the list */
	FWHAttributeChangeDelegate OnAttributeRemovedDelegate;

	/** Delegate called when an attribute is added to the list */
	FWHAttributeChangeDelegate OnAttributeAddedDelegate;


	template<typename T>
	void SetAttribute(const FWHAttributeValue& NewValue)
	{
		if (FWHAttributeValue* const Attr = FindAttributeValue(NewValue.Ref))
		{
			*Attr = NewValue;
			MarkItemDirty(*Attr);
			return;
		}
		auto& NewAttribute = Attributes.Add_GetRef(NewValue);
		MarkItemDirty(NewAttribute);
		MarkArrayDirty();
	}
};


/** Specify custom functions to look for in FWHAttributeContainer */
template<>
struct TStructOpsTypeTraits<FWHAttributeContainer> : public TStructOpsTypeTraitsBase2<FWHAttributeContainer>
{
	enum
	{
		WithSerializer                 = true,                         // struct has a Serialize function for serializing its state to an FArchive.
		WithNetSerializer              = true,                         // struct has a NetSerialize function for serializing its state to an FArchive used for network replication.
		WithNetDeltaSerializer         = true,                         // struct has a NetDeltaSerialize function for serializing differences in state from a previous NetSerialize operation.
	};
};
