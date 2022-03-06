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
	FORCEINLINE static const UWHAttributeSubsystem* Get() {return GEngine->GetEngineSubsystem<UWHAttributeSubsystem>();}

	/**
	 *	Get an ID from it's associated Human-readable name
	 *	@note You don't need to use it in your game systems
	 */
	static FGuid GetIDForName(const FName& Name);

	/**
	 *	Get a Human-readable name from an ID
	 *	@note You don't need to use it in your game systems
	 */
	static const FName& GetNameForID(const FGuid& GUID);



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
	UPROPERTY(Transient)
	TMap<FGuid, FName> GameAttributes;

	/**
	 *	Fill our data with what's in settings
	 */
	UFUNCTION()
	void ImportSettings();

	/**
	 *	Update the settings to match what we have
	 */
	UFUNCTION()
	void ExportSettings();

#if WITH_EDITOR
	// Callbacks for refreshing the subsystems from changes in the settings
	void OnObjectPreSave(UObject* ModifiedObject, FObjectPreSaveContext Context);
	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);

	// save changes to the settings on shutdown
	void OnEnginePreExit();

	// stored delegates
	FDelegateHandle OnObjectPreSaveDelegate;
	FDelegateHandle OnObjectPropertyChangedDelegate;
	FDelegateHandle OnEnginePreExitDelegate;

#endif WITH_EDITOR



};
