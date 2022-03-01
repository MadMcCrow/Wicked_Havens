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
