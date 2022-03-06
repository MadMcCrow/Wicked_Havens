/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Misc/Guid.h"
#include "WHAttributeName.generated.h"


/**
 *	A struct for representing an attribute (not it's value)
 *	It's meant to have a 1-1 relation to the names in the settings.
 */
USTRUCT(BlueprintType, Category="Attributes")
struct WH_ATTRIBUTES_API FWHAttributeName
{
	GENERATED_BODY()

private:

	/**
	 *	Attribute Name for Chad machines
	 *	(it's meant for comparison and unicity)
	 */
	UPROPERTY()
	FGuid UniqueID;

public:

	// Various CTRs
	FWHAttributeName(); // BAD !
	FWHAttributeName(const FName& AttributeName); // GOOD
	FWHAttributeName(const FGuid& AttributeID) : UniqueID(AttributeID) {} // GOOD
	explicit FWHAttributeName(const FString& AttributeIDString) : UniqueID(AttributeIDString) {} // ALSO GOOD
	FWHAttributeName(const FWHAttributeName& InAttribute); // COPY
	FWHAttributeName& operator=(const FWHAttributeName& Other); // ALSO COPY

	// ONLY CHECK UID
	FORCEINLINE bool operator==(const FWHAttributeName& Other) const {return UniqueID == Other.UniqueID;}

	// Friendly functions, yeah !
	FORCEINLINE friend uint32 GetTypeHash(const FWHAttributeName& Item)		{return GetTypeHash(Item.UniqueID);}
	friend FArchive& operator<<(FArchive& Ar, FWHAttributeName& AttrName) { AttrName.UniqueID.Serialize(Ar); return Ar;}


	/**
	 *	retrun the name associated in the settings,
	 *	or NAME_None if not found
	 */
	const FName& GetName() const;

	// operator for above function
	FORCEINLINE explicit operator FName() const {return GetName();}


	/**
	 *	Verifies there's a valid name registered in the settings
	 */
	bool IsValid() const;

	/** Getter for GUID */
	FORCEINLINE const FGuid& GetID() const {return UniqueID;}

	/** Gets GUID as string, correctly formatted for use in and out of editor */
	FString ExportIDString() const;

#if WITH_EDITOR
	// Import/Export function (for Editor)
	static FString Export(const FWHAttributeName& Name);
	static FWHAttributeName Import(const FString& String);
#endif //WITH_EDITOR

};
