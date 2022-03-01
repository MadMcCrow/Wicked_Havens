/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeValue.generated.h"



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


	/**
	 *	For now we store the value with an FVariant
	 *	Ideally we would store the data another way
	 *	Because Variant are really limited as a type
	 *	(for instance, no array, no FText, etc...)
	 *	TODO: have an array of UINT8 and fast serialize it.
	 */
	FVariant StoredValue;

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
