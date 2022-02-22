/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "WHAttributeContainer.generated.h"

struct FWHAttributeName;
struct FWHAttributeValue;

// Multicast for FWHAttributeContainer
DECLARE_MULTICAST_DELEGATE_TwoParams(FWHAttributeChangeDelegate, FWHAttributeName, FWHAttributeValue)


/**
 *	A struct for representing an attribute (not it's value)
 *	It's just a "name-sake" for an int, but it's far more readable.
 *	@todo : Add "Make" and "Break" functions to help
 */
USTRUCT(BlueprintType)
struct WH_ATTRIBUTES_API FWHAttributeName
{
	GENERATED_BODY()

private:

	// Blueprint Enums can go quite far in values
	UPROPERTY()
	int64 EnumValue;

public:

	// Various CTRs
	FWHAttributeName(const FName& AttributeName);
	FWHAttributeName(int64 AttributeValue = INDEX_NONE) : EnumValue(AttributeValue) {}

	bool operator==(const FWHAttributeName& Other) const {return EnumValue == Other.EnumValue;}

	friend FArchive& operator<<(FArchive& Ar, FWHAttributeName Name ){	return Ar << Name.EnumValue;}

	explicit operator FName() const;
};


/**
 *	A struct for representing the value of an Attribute
 *	Attributes can be floats, integers, names, booleans, texts, etc... (as long as it serializes)
 */
USTRUCT(BlueprintType)
struct WH_ATTRIBUTES_API FWHAttributeValue
{
	GENERATED_BODY()

public:
	// CTRs and copy
	FWHAttributeValue(){}
	FWHAttributeValue(const FWHAttributeValue& RHS) = default;
	FWHAttributeValue(FWHAttributeValue&&) = default;
	FWHAttributeValue& operator=(FWHAttributeValue&&) = default;
	FWHAttributeValue& operator=(const FWHAttributeValue& RHS) = default;

	// this cannot be a uproperty, I hope it is not too much of a problem :/
	FVariant StoredValue;

	// useful operations
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeValue Value ){	return Ar << Value.StoredValue;}
	FORCEINLINE friend bool operator==(const FWHAttributeValue& LHS, const FWHAttributeValue& RHS){return LHS.StoredValue == RHS.StoredValue;}

	// set from anything
	template<typename T>
	FWHAttributeValue& operator=(const T &Value)	{StoredValue = Value; return *this;}

	// get as anything
	template<typename T>
	operator T() const {return StoredValue;}

};


/**
 *	An Element for @see FWHAttributeContainer
 *	Specifically adapted to fast replication
 */
USTRUCT(BlueprintType, Category = "Attributes",
	 meta = (	HasNativeBreak = "WH_Attributes.WHAttributesLibrary.BreakAttribute",
				 HasNativeMake  = "WH_Attributes.WHAttributesLibrary.MakeAttribute"))
struct FWHAttribute : public FFastArraySerializerItem
{
	GENERATED_BODY()
	friend struct FWHAttributeContainer;

	// CTRs :
	FWHAttribute() : FFastArraySerializerItem() {}
	FWHAttribute(const TPairInitializer<FWHAttributeName, FWHAttributeValue>& InitPair)
	: FFastArraySerializerItem(), Name(InitPair.Key), Value(InitPair.Value)
	{}


	/** the name, acts like a key in a map */
	UPROPERTY()
	FWHAttributeName Name;

	/** the associated value */
	UPROPERTY()
	FWHAttributeValue Value;

	/** Called by NetSerialize of FWHAttributeContainer */
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttribute Attribute )
	{
		Ar << Attribute.Name;
		Ar << Attribute.Value;
		return Ar;
	}

	// Replication Functions
	void PostReplicatedAdd(		const struct FWHAttributeContainer& InArraySerializer) const;
	void PostReplicatedChange(	const struct FWHAttributeContainer& InArraySerializer) const;
	void PreReplicatedRemove(	const struct FWHAttributeContainer& InArraySerializer) const;

	// comparison operator for Array operations
	bool operator==(const FWHAttribute& Other) const {return Name == Other.Name && Value == Other.Value;}

};

/**
 *	A struct to contain a list of attributes
 *	@todo Break and Make functions
 */
USTRUCT(BlueprintType, Category = "Attributes",
	 meta = (	HasNativeBreak = "WH_Attributes.WHAttributesLibrary.BreakAttributeContainer",
	 			HasNativeMake  = "WH_Attributes.WHAttributesLibrary.MakeAttributeContainer"))
struct WH_ATTRIBUTES_API FWHAttributeContainer : public FFastArraySerializer
{
	GENERATED_BODY()
public:

	// Begin Serialization -----
	bool Serialize(FArchive& Ar);
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);
	// End Serialization -----


	/**
	 *	Set all attributes at once, (empties the stored attributes)
	 */
	void InitAttributes(const TArray<FWHAttribute> InAttributes);

	/**
	 *	Adds an attribute to the already stored ones
	 *	(if one with the same name already present, updates it)
	 */
	void AddOrChangeAttribute(const FWHAttribute& Attribute);

	/**
	 *	Remove the attribute associated with this name
	 *	@return true if removed something
	 */
	bool RemoveAttribute(const FWHAttributeName& AttributeName);

	/**
	 *	Get the attribute with the associated name
	 *	@return pointer to the attribute, or nullptr if not present
	 */
	const FWHAttribute* GetAttributeByName(const FWHAttributeName& AttributeName) const;

	/**
	 *	Get the attribute with the associated name
	 *	mutable version
	 *	@return pointer to the attribute, or nullptr if not present
	 */
	 FWHAttribute* GetAttributeByName(const FWHAttributeName& AttributeName);

	/**
	 * return all the attributes, does not let you change them
	 */
	FORCEINLINE const TArray<FWHAttribute>& GetAllAttributes() const {return Attributes;}



private:
    /**
     * The list of Attributes
     */
    UPROPERTY()
    TArray<FWHAttribute> Attributes;

public:

	/** Delegate called on each changes of every attribute */
	FWHAttributeChangeDelegate OnAttributeChangedDelegate;

	/** Delegate called when an attribute is removed from the list */
	FWHAttributeChangeDelegate OnAttributeRemovedDelegate;

	/** Delegate called when an attribute is added to the list */
	FWHAttributeChangeDelegate OnAttributeAddedDelegate;

};


/** Specify custom functions to look for in FWHInventory */
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
