/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeType.generated.h"



/**
 *	@struct FWHAttributeType
 *	A struct for representing the Type of an Attribute
 *	Attributes can be floats, integers, names, booleans, texts, etc... (as long as it serializes)
 *	To achieve this, we use this struct to inform us on how to store, serialize, etc
 */
USTRUCT(BlueprintType, Category = "Attributes")
struct WH_ATTRIBUTES_API FWHAttributeType
{
	GENERATED_BODY()

	// the field class to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
	FString FieldClassName;

	// for field Classes that takes a struct, that's the type to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
	TObjectPtr<UField> CppField;


};
