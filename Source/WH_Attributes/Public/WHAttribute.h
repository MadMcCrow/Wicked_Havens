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
USTRUCT(BlueprintType, Category = "Wicked Havens|Attributes")
struct WH_ATTRIBUTES_API FWHAttributeRef
{
	GENERATED_BODY()

	// Default CTR
	FWHAttributeRef() = default;

	// CTR with object as parameter
	FWHAttributeRef(const class UWHAttributeBase* AttributeObject);

	// CTR with class
	explicit FWHAttributeRef(const TSubclassOf<UWHAttributeBase> AttributeClass);
	explicit FWHAttributeRef(const UClass* AttributeClass);

private:
	/**
	 *	Ref
	 *	Unique way of referencing attributes.
	 *	for now we use a soft class path, but we could prefer a FGuid or anything else that ensure uniqueness
	 */
	UPROPERTY()
	FSoftClassPath Ref;

public:
	
	FORCEINLINE FString ToString() const{return Ref.ToString();}
	FORCEINLINE operator FString() const{return ToString();}
	FORCEINLINE TSubclassOf<UWHAttributeBase> GetAttributeClass() const {return Ref.TryLoadClass<UWHAttributeBase>();}
	
	FORCEINLINE bool IsValid() const {return Ref.IsValid();}
	
	FORCEINLINE bool operator==(const FWHAttributeRef& lhs) const {return Ref == lhs.Ref;}
	FORCEINLINE bool operator!=(const FWHAttributeRef& lhs) const {return !operator==(lhs);}
	
	FORCEINLINE friend FArchive& operator<<(FArchive& Ar, FWHAttributeRef& InRef) { return Ar << InRef.Ref;}
	FORCEINLINE friend int32 GetTypeHash(const FWHAttributeRef& InRef) {return GetTypeHash(InRef.Ref);}

};

/**
 *	UWHAttributeBase is a class used to defined an attribute
 *	derive it and define your Guid to create your custom attributes
 */
UCLASS(Abstract, Blueprintable, Category = "Wicked Havens|Attributes")
class WH_ATTRIBUTES_API UWHAttributeBase : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * If you have native variables (non-UProperty), you'll need to override Serialize 
	 */
	virtual void Serialize(FArchive& Ar) override;

	/**
	 *	Event to get a representation of the attribute, for debug and editor purposes
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintCosmetic, Category= "Attribute")
	FString ToString() const;
	virtual FString ToString_Implementation() const;
	
};
