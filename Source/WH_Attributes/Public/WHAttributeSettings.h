/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeName.h"
#include "WHAttributeType.h"
#include "Engine/DeveloperSettings.h"
#include "WHAttributeSettings.generated.h"

/**
 * Defines an attribute for your game
 */
USTRUCT(BlueprintType, Category="Attributes")
struct FWHAttributeDefinition
{
	GENERATED_BODY()
	friend class UWHAttributeSettings;

protected:
	/**	Attribute Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	/**	Attribute Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWHAttributeType Type;

	/**	Used both in game and in editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	/**	ID. Generated Once */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, AdvancedDisplay)
	FGuid UniqueID;

public:

	FORCEINLINE TPair<FGuid, FWHAttributeType>	GetAttributeTypeDefinition() const {return	{UniqueID,Type};}
	FORCEINLINE TPair<FGuid, FName>				GetAttributeNameDefinition() const {return	{UniqueID,Name};}
};



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

	// Quick Getter for Attribute definitions
	FORCEINLINE const TArray<FWHAttributeDefinition>& GetAttributeDefinitions() const {return AttributeDefinitions;}


private:

	/**
	 *	The attributes for your Game
	 */
	UPROPERTY(Config, EditAnywhere, meta = (AllowPrivateAccess))
	TArray<FWHAttributeDefinition> AttributeDefinitions;

public:

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR

};
