/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeValue.generated.h"

// TODO : Support Array of Ints, Array of Names, Array of Strings, Array of Objects

/**
 *	@enum EWHAttributeTypes
 *	Describe what type an attribute can have
 */
UENUM(BlueprintType, Category="Attributes")
enum class EWHAttributeTypes : uint8
{
	TError		UMETA(DisplayName="Error",		Tooltip="invalid attribute type"),
	TMultiple	UMETA(DisplayName="Multiple",	Tooltip="Can be different types"),
	TBool		UMETA(DisplayName="Bool",		Tooltip="bool"),
	TInt		UMETA(DisplayName="Int",		Tooltip="int32"),
	TInt64		UMETA(DisplayName="Int64",		Tooltip="int64"),
	TFloat		UMETA(DisplayName="Float",		Tooltip="float"),
	TString		UMETA(DisplayName="String",		Tooltip="FString"),
	TName		UMETA(DisplayName="Name",		Tooltip="FName"),
	TByte		UMETA(DisplayName="Byte",		Tooltip="uint8"),
	TEnum		UMETA(DisplayName="Enum",		Tooltip="uint8"),
	TText		UMETA(DisplayName="Text",		Tooltip="FText"),
	TVector		UMETA(DisplayName="Vector",		Tooltip="FVector"),
	TRotator	UMETA(DisplayName="Rotator",	Tooltip="FRotator"),
	TColor		UMETA(DisplayName="Color",		Tooltip="FColor"),
	TTransform	UMETA(DisplayName="Transform",	Tooltip="FTransform"),
	TArray		UMETA(DisplayName="Array",		Tooltip="TArray"),
	TObject		UMETA(DisplayName="Object",		Tooltip="TObjectPtr")
};


static CONSTEXPR EVariantTypes AttributeTypeToVariantType(EWHAttributeTypes InAttributeType)
{
	switch (InAttributeType)
	{
	default:
	case EWHAttributeTypes::TError:		return EVariantTypes::Empty;
	case EWHAttributeTypes::TBool:		return EVariantTypes::Bool;
	case EWHAttributeTypes::TInt:		return EVariantTypes::Int32;
	case EWHAttributeTypes::TInt64:		return EVariantTypes::Int64;
	case EWHAttributeTypes::TFloat:		return EVariantTypes::Float;
	case EWHAttributeTypes::TString:	return EVariantTypes::String;
	case EWHAttributeTypes::TByte:		return EVariantTypes::UInt8;
	case EWHAttributeTypes::TEnum:		return EVariantTypes::Enum;
	case EWHAttributeTypes::TVector:	return EVariantTypes::Vector;
	case EWHAttributeTypes::TRotator:	return EVariantTypes::Rotator;
	case EWHAttributeTypes::TTransform:	return EVariantTypes::Transform;
	case EWHAttributeTypes::TText:		return EVariantTypes::Custom;
	case EWHAttributeTypes::TArray: 	return EVariantTypes::Custom;
	case EWHAttributeTypes::TObject:	return EVariantTypes::Custom;
	}
}

static CONSTEXPR EWHAttributeTypes VariantTypeToAttributeType(EVariantTypes InVariantType)
{
	switch (InVariantType)
	{
	default:
	case EVariantTypes::Empty:		return EWHAttributeTypes::TError;
	case EVariantTypes::Bool:		return EWHAttributeTypes::TBool;
	case EVariantTypes::Color:		return EWHAttributeTypes::TColor;
	case EVariantTypes::Enum: 		return EWHAttributeTypes::TEnum;
	case EVariantTypes::Float:		return EWHAttributeTypes::TFloat;
	case EVariantTypes::Int32:		return EWHAttributeTypes::TInt;
	case EVariantTypes::Int64: 		return EWHAttributeTypes::TInt64;
	case EVariantTypes::Name: 		return EWHAttributeTypes::TName;
	case EVariantTypes::Rotator: 	return EWHAttributeTypes::TRotator;
	case EVariantTypes::String: 	return EWHAttributeTypes::TString;
	case EVariantTypes::Transform:	return EWHAttributeTypes::TTransform;
	case EVariantTypes::UInt8:		return EWHAttributeTypes::TByte;
	case EVariantTypes::Vector:		return EWHAttributeTypes::TVector;
	case EVariantTypes::Custom:		return EWHAttributeTypes::TMultiple;
	}
}



template<typename T> struct TCustomVariantTraits
{
	static CONSTEXPR EWHAttributeTypes GetWHType()
	{
		const auto VariantType = TVariantTraits<T>::GetType();
		if (VariantType != EVariantTypes::Custom){return VariantTypeToAttributeType(VariantType);}
		return EWHAttributeTypes::TError;
	}
};

/** Implements variant type traits for FTexts */
template<> struct TVariantTraits<FText>
{
	static CONSTEXPR EVariantTypes GetType() { return EVariantTypes::Custom; }
};
template<> struct TCustomVariantTraits<FText>
{
	static CONSTEXPR EWHAttributeTypes GetWHType() { return EWHAttributeTypes::TText; }
};

template<> struct TVariantTraits<TObjectPtr<UObject>>
{
	static CONSTEXPR EVariantTypes GetType() { return EVariantTypes::Custom; }
};
template<> struct TCustomVariantTraits<UObject>
{
	static CONSTEXPR EWHAttributeTypes GetWHType() { return EWHAttributeTypes::TObject; }
};



/**
 * this is the struct responsible for being a variant for the FWHAttributeValue
 * this is an extension of FVariant to support more types
 */

struct FWHAttributeValuePrivate : public FVariant
{
	// Attribute supported type
	EWHAttributeTypes WHType;

	// CTR
	FWHAttributeValuePrivate() :
	FVariant(),
	WHType(EWHAttributeTypes::TError)
	{

	}

	// CTR by Ref
	template<typename T>
	FWHAttributeValuePrivate(const T& InValue) :
	FVariant(InValue),
	WHType(TCustomVariantTraits<T>::GetWHType())
	{
	}

	// COPY (Ref)
	template<typename T>
	FWHAttributeValuePrivate& operator=(const T& InValue )
	{
		WHType = TCustomVariantTraits<T>::GetWHType();
		*this = FVariant(InValue);
		return *this;
	}
};

/**
 *	@struct FWHAttributeValue
 *	A struct for representing the value of an Attribute
 *	Attributes can be floats, integers, names, booleans, texts, etc... (as long as it serializes)
 */
USTRUCT(BlueprintType, Category="Attributes")
struct FWHAttributeValue
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
	 *	This is a custom Variant that can handle way more than just common types
	 */
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
