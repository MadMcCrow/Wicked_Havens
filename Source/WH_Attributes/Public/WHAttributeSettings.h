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

public:
	// CTR !
	UWHAttributeSettings();

	// Category override :
	virtual FName GetCategoryName() const override {return FName("Wicked Havens");}

	// Updates our runtime AttributeDefinitions to match our settings
	void Initialize();

	// Quick helper functions used in game and editor
	// these are not to be read directly by your systems
	FGuid GetIDForName(const FName& Name) const;
	FName GetNameForID(const FGuid& GUID) const;


	// Helper function meant for the Editor
#if WITH_EDITOR
	WH_ATTRIBUTES_API void GetAllNames(TArray<FName>&OutNames) const;
#endif WITH_EDITOR



protected:


    /**
     *	A Datatable containing all the different attributes to use in Wicked Havens
     */
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Attributes",  meta=(AllowedClasses="DataTable", RequiredAssetDataTags = "RowStructure=WHAttributeDefinition"))
    FSoftObjectPath AttributesDataTable;

	/**
	 *	Attributes from @see AttributesDataTable, but easily fetched
	 *	Please don't make a joke about my attributes being private
	 */
	TMap<FGuid, FName> PrivateAttributes;
	TMap<FName, FGuid> ReversedPrivateAttributes;

#if WITH_EDITOR
	// On Change property, re-initialize
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// On Properties initialized, Initialize
	virtual void PostInitProperties() override;
	// On Object PreSave, called from the engine itself
	void OnObjectPreSave(UObject* ModifiedObject, FObjectPreSaveContext Context);
	FDelegateHandle OnObjectPreSaveDelegate;
#endif WITH_EDITOR


private:

	FGuid GetGUIDForEntry(const FName EntryName, const struct FWHAttributeDefinition& Definition) const;
};
