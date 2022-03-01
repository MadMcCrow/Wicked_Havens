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

	void Initialize();

	FGuid GetIDForName(const FName& Name) const;
	FName GetNameForID(const FGuid& GUID) const;
	void GetAllNames(TArray<FName>&OutNames) const;

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
	virtual void PostInitProperties() override;
	// On Object PreSave, called from the engine itself
	void OnObjectPreSave(UObject* ModifiedObject, FObjectPreSaveContext Context);
	FDelegateHandle OnObjectPreSaveDelegate;
#endif WITH_EDITOR

};
