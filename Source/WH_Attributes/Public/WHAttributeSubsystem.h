/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "WHAttributeSubsystem.generated.h"



/**
 *	@class UWHAttributeSettings
 *	@brief Store and helps generate all the attribute names and GUIDs
 */
UCLASS(MinimalAPI, ClassGroup=(WH), Category="Attributes", Meta = (DisplayName="Attributes Subsystem"))
class UWHAttributeSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
	// CTR !
	UWHAttributeSubsystem();

	// <UEngineSubsystem-API>
	virtual void Initialize(FSubsystemCollectionBase & Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Deinitialize() override;
	// <\UEngineSubsystem-API>


	// Helper Getter
	FORCEINLINE static UWHAttributeSubsystem* Get() {return GEngine->GetEngineSubsystem<UWHAttributeSubsystem>();}

	const struct FWHAttributeType& GetAttributeType(const struct FWHAttributeName& InName);
	const FName& GetAttributeFName(const struct FWHAttributeName& InName);

	struct FWHAttributeName FindAttributeName(const FName& InFName);


	/**
	 *	Fill our data with what's in settings
	 */
	UFUNCTION()
	void ImportSettings();


#if WITH_EDITOR
	/**
	 *	Helper function meant for the Editor
	 *	Will Get all names for editor Picker tools
	 */
	WH_ATTRIBUTES_API static void GetAllNames(TArray<FName>&OutNames);
#endif WITH_EDITOR

private:

	/**
	 *	Attributes from @see UWHAttributeSettings::AttributesDataTable
	 *	GUIDs are generated (hopefully) only once.
	 */
	TMap<FGuid, FName> GameAttributeNames;

	/**
	 *	Attributes from @see UWHAttributeSettings::AttributesDataTable
	 *	GUIDs are generated (hopefully) only once.
	 */
	TMap<FGuid, FWHAttributeType*> GameAttributeTypes;


	/** List of all CDO of FFieldClass in the Engine */
	TMap<FString,FField*> FieldClassDefaultObjects;

	void InitializeAllTypes();







};
