/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WHAttributeSettings.generated.h"


/**
 *	@class UWHAttributeSettings
 *	@brief Store and helps generate all the attribute names and GUIDs
 */
UCLASS(MinimalAPI, ClassGroup=(WH), config=Game, Category="Attributes", Meta = (DisplayName="Attributes Settings", ToolTip = "Settings for the Attributes system : Set Attributes definitions here"))
class UWHAttributeSettings : public UDeveloperSettings
{
    GENERATED_BODY()
	friend class UWHAttributeSubsystem;

public:
	// CTR !
	UWHAttributeSettings();

	// Category override :
	virtual FName GetCategoryName() const override {return FName("Wicked Havens");}


protected:


    /**
     *	A Datatable containing all the different attributes to use in Wicked Havens
     */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Attributes",  meta=(AllowedClasses="DataTable", RequiredAssetDataTags = "RowStructure=WHAttributeDefinition"))
    FSoftObjectPath AttributesDataTable;

	/**
	 *	Attributes from @see AttributesDataTable
	 *	GUIDs are generated (hopefully) only once.
	 */
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category="Attributes", AdvancedDisplay)
	TMap<FGuid, FName> SavedGameAttributes;



};
