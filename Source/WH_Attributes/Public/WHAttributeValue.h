/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "Misc/AssertionMacros.h"
#include "Containers/Array.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include "WHAttributeValue.generated.h"

/**
 * @struct	FWHAttributeValue
 */
USTRUCT()
struct FWHAttributeValue
{
	GENERATED_BODY()

	/**
	 *	PrivateData
	 *	Everything we store is stored as an array of bytes
	 *	this means we can only restitute the data if we know what it was
	 */
	TArray<uint8> Value;


	template<typename T>
	T GetValue() const
	{
		T Result;
		FMemoryReader Reader(Value, true);
		Reader << Result;
		return Result;
	}

	template<typename T>
	operator T() const
	{
		return GetValue<T>();
	}

	template<typename T>
	FWHAttributeValue(T InValue)
	{
		FMemoryWriter Writer(Value, true);
		Writer << InValue;
	}

	template<typename T>
	FWHAttributeValue& operator=( T InValue )
	{
		FMemoryWriter Writer(Value, true);
		Writer << InValue;
		return *this;
	}

	// Compare two values
	friend bool operator==(const FWHAttributeValue& LHS, const FWHAttributeValue& RHS)
	{
		return  LHS.Value == RHS.Value;
	}

	friend FArchive& operator<<(FArchive& Ar, FWHAttributeValue Attribute )
	{
		Ar << Attribute.Value;
		return Ar;
	}

	FWHAttributeValue() = default;
	~FWHAttributeValue() = default;
};
