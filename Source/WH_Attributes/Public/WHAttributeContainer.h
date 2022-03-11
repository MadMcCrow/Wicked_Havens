/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "WHAttributeName.h"
#include "WHAttributeValue.h"
#include "WHAttributeContainer.generated.h"


// Multicast for FWHAttributeContainer
DECLARE_MULTICAST_DELEGATE_TwoParams(FWHAttributeChangeDelegate, FWHAttributeName, FWHAttributeValue)

/**
 *	An Element for @see FWHAttributeContainer
 *	Specifically adapted to fast replication
 */
USTRUCT(BlueprintType, Category = "Attributes")
struct FWHAttribute : public FFastArraySerializerItem
{
	GENERATED_BODY()
	friend struct FWHAttributeContainer;

	// CTRs :
	FWHAttribute() : FFastArraySerializerItem() {}

	/** the name, acts like a key in a map */
	UPROPERTY()
	FWHAttributeName Name;

	/** the value, acts like a value in a map */
	UPROPERTY()
	FWHAttributeValue Value;

	/** Called by NetSerialize of FWHAttributeContainer */
	friend FArchive& operator<<(FArchive& Ar, FWHAttribute Attribute )
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
	 meta = (	HasNativeBreak = "WH_Attributes.WHAttributeFunctionLibrary.BreakAttributeContainer",
	 			HasNativeMake  = "WH_Attributes.WHAttributeFunctionLibrary.MakeAttributeContainer"))
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
    UPROPERTY(EditAnywhere)
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
