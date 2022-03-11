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

	// CTR
	FWHAttributeName(FGuid AttributeID = FGuid()) : UniqueID(AttributeID){} // from Guid
	FWHAttributeName(const FWHAttributeName& InAttribute); // COPY
	FWHAttributeName& operator=(const FWHAttributeName& Other); // ALSO COPY
	explicit FWHAttributeName(FName AttributeName);
	// ONLY CHECK UID
	FORCEINLINE bool operator==(const FWHAttributeName& Other) const {return UniqueID == Other.UniqueID;}

	// Friendly functions, yeah !
	FORCEINLINE friend uint32 GetTypeHash(const FWHAttributeName& Item)		{return GetTypeHash(Item.UniqueID);}
	friend FArchive& operator<<(FArchive& Ar, FWHAttributeName& AttrName) { AttrName.UniqueID.Serialize(Ar); return Ar;}


	//	return the name associated in the settings
	const FName& GetName() const;
	FORCEINLINE operator FName() const {return GetName();} 	// operator for above function
	FORCEINLINE const FGuid& GetID() const {return UniqueID;}
	FORCEINLINE bool IsValid() const {return GetID()!= FGuid() && GetName() != NAME_None;}

	/** Gets GUID as string, correctly formatted for use in and out of editor */
	FString ExportIDString() const;

#if WITH_EDITOR
	// Import/Export function (for Editor)
	static FString Export(const FWHAttributeName& Name);
	static FWHAttributeName Import(const FString& String);
#endif //WITH_EDITOR
};
