/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttribute.generated.h"

/**
 *	@struct FWHAttributeRef
 *	Easy way to reference an attribute type
 *	@note
 *			- This acts as both an attribute Name And Type
 *			- For editor, we need a customisation to edit these
 */
USTRUCT(BlueprintType)
struct FWHAttributeRef
{
	GENERATED_BODY()

	// Default CTR
	FWHAttributeRef() = default;

	// CTR with object as parameter
	FWHAttributeRef(const class UWHAttributeBase* AttributeObject);

	/** Reference Class directly in it (maybe a better way to do this) */
	UPROPERTY()
	FSoftClassPath Path;
	

	FORCEINLINE bool operator==(const FWHAttributeRef& lhs) const {return Path == lhs.Path;}
	FORCEINLINE bool operator!=(const FWHAttributeRef& lhs) const {return !operator==(lhs);}
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeRef& Ref) { return Ar << Ref.Path;}
	FORCEINLINE friend int32 GetTypeHash(const FWHAttributeRef& InRef) {return GetTypeHash(InRef.Path);}
};

/**
 *	UWHAttributeBase is a class used to defined an attribute
 *	derive it and define your Guid to create your custom attributes
 */
UCLASS(Abstract, Blueprintable, Category= "Attribute")
class UWHAttributeBase : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * If you have native variables (non-UProperty), you'll need to override Serialize 
	 */
	virtual void Serialize(FArchive& Ar) override;
};
