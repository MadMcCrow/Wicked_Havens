/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeValue.generated.h"

/**
 * this is the struct responsible for being a variant for the FWHAttributeValue
 */
USTRUCT()
struct FWHAttributeValuePrivate
{
	GENERATED_BODY()

	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeValuePrivate Value )
	{
		return Ar;
	}
	FORCEINLINE friend bool operator==(const FWHAttributeValuePrivate& LHS, const FWHAttributeValuePrivate& RHS)
	{
		return true;
	}

	template<typename T>
	operator T() const
	{
		T Value;
		return Value;
	}

	template<typename T>
	FWHAttributeValuePrivate(T Value)
	{

	}

	FWHAttributeValuePrivate() = default;
	~FWHAttributeValuePrivate() = default;
};

/**
 *	@struct FWHAttributeValue
 *	A struct for representing the value of an Attribute
 *	Attributes can be floats, integers, names, booleans, texts, etc... (as long as it serializes)
 */
USTRUCT(BlueprintType, Category="Attributes")
struct WH_ATTRIBUTES_API FWHAttributeValue
{
	GENERATED_BODY()

public:
	// CTRs and copy
	FWHAttributeValue()
	{

	}
	FWHAttributeValue(const FWHAttributeValue& RHS) = default;
	FWHAttributeValue(FWHAttributeValue&&) = default;
	FWHAttributeValue& operator=(FWHAttributeValue&&) = default;
	FWHAttributeValue& operator=(const FWHAttributeValue& RHS) = default;


	/**
	 *	This is a custom Variant that can handle way more than just common types
	 */
	UPROPERTY()
	FWHAttributeValuePrivate StoredValue;

	// useful operations
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeValue Value ){	return Ar << Value.StoredValue;}
	FORCEINLINE friend bool operator==(const FWHAttributeValue& LHS, const FWHAttributeValue& RHS){return LHS.StoredValue == RHS.StoredValue;}

	// set from anything
	template<typename T>
	FWHAttributeValue& operator=(const T &Value)	{StoredValue = Value; return *this;}

	// Set and Get :
	// TODO: Perform checks  on types :
	// get as anything
	template<typename T>
	operator T() const {return StoredValue;}

	// Set from anything : template constructor
	template<typename T>
	FWHAttributeValue(T Value) : StoredValue(Value) {}

};
