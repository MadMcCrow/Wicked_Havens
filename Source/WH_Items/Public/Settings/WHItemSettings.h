/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Engine/DeveloperSettings.h"
#include "WHItemSettings.generated.h"


/**
 *	@class UWHItemSettings
 *	@brief A simple way to set @see UWHItemSubsystem Items.
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName=ItemSettings), Category="Wicked Havens|Items", MinimalAPI)
class UWHItemSettings : public UDeveloperSettings
{
    GENERATED_BODY()
	friend class UWHItemSubsystem;

public:

	// Category override :
	virtual FName GetCategoryName() const override {return FName("Wicked Havens");}
protected:

    /**
     *	A datatable containing all the items
     *	@todo : make an array of those, allow for different DLCs etc...
     */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Items", meta=(AllowedClasses="DataTable", RequiredAssetDataTags = "RowStructure=WHItemTableRow"))
    FSoftObjectPath ItemDatatable;

	/** Will load async @see ItemDatatable, and call a FSimpleDelegate on completion */
	FSimpleDelegate LoadDatable() const;

	/** Resolves object, will not load */
	class UDataTable* GetDatatable() const;
};
