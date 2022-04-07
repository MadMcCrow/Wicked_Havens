/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "WHAttribute.h"
#include "WHAttributeSubsystem.generated.h"

/** Forward declaration */
class UWHAttributeBase;

/**
 *	@class UWHAttributeSubsystem
 *	@brief Store and helps generate all the attributes
 */
UCLASS(MinimalAPI, ClassGroup=(WH), Category="Attributes", Meta = (DisplayName="Attributes Subsystem"))
class UWHAttributeSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()
	friend FWHAttributeRef;

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 *	Get an attribute object ready for operation on attributes.
	 *	@todo : Pool those object to gain performance
	 */
	static UWHAttributeBase* GetAttributeObject(const FWHAttributeRef& Ref);

	
protected:

	/** Get all attribute in the game and store them */
	void RefreshAttributes();
	
private:

	/** Store all Attributes Object used in your game */
	UPROPERTY(Transient)
	TMap<FWHAttributeRef, UWHAttributeBase*> AttributeObjects;

#if WITH_EDITOR
	void OnObjectPreSave(UObject* SavedObject, FObjectPreSaveContext Context);
	FDelegateHandle OnPreSaveDelegate;
#endif // WITH_EDITOR
	
};
