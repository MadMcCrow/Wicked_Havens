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

	// The C++ data type of the variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
	FString CPPType;

	// The Struct of the C++ data type of the variable (or nullptr)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
	TObjectPtr<UObject> CPPTypeObject = nullptr;

	// The default value of the variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
	FString DefaultValue;



	static FString Export(const FWHAttributeType& Name, FWHAttributeType DefaultValue = FWHAttributeType());
	static FWHAttributeType Import(const FString& String);

#if WITH_EDITOR
	/** Return the type in the TArray if Array type */
	TOptional<FString> GetArrayBaseType() const;

	/** returns true if TArray */
	bool IsArrayType() const;

#endif // WITH_EDITOR
};
