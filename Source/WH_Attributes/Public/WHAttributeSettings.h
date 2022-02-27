/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WHAttributeSettings.generated.h"


/**
 *	@class UWHAttributeSettings
 *	@brief Store and helps generate all the attribute names and GUIDs
 */
UCLASS(ClassGroup=(WH), config=Game, Category="Attributes")
class WH_ATTRIBUTES_API UWHAttributeSettings : public UDeveloperSettings
{
    GENERATED_BODY()


public:
	// CTR !
	UWHAttributeSettings();

	FGuid GetIDForName(const FName& Name) const;
	FName GetNameForID(const FGuid& GUID) const;
	void GetAllNames(TArray<FName>&OutNames) const;

protected:

    /**
     *	A Datatable containing all the different attributes to use in Wicked Havens
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes",  meta=(AllowedClasses="DataTable", RequiredAssetDataTags = "RowStructure=WHAttributeDefinition"))
    FSoftObjectPath AttributesDataTable;

	/**
	 *	Attributes from @see AttributesDataTable, but easily fetched
	 *	Please don't make a joke about my attributes being private
	 */
	TMap<FGuid, FName> PrivateAttributes;
	TMap<FName, FGuid> ReversedPrivateAttributes;

};
