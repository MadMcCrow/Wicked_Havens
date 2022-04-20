/* Copyright © Noé Perard-Gayot 2022. */

#pragma once


#include "Engine/DeveloperSettings.h"
#include "WHActionSettings.generated.h"

// forward declaration:
class UWHActionBase;


/**
 *	@class UWHActionSettings
 *	@brief Set all the parameters to have working Actions in Wicked Havens
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName=Actions), Category="Wicked Havens|Actions", MinimalAPI)
class UWHActionSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	friend class UWHActionSubsystem;

public:

	UWHActionSettings(const FObjectInitializer& ObjectInitializer);
	
	// Category override :
	virtual FName GetCategoryName() const override {return FName("Wicked Havens");}
	
protected:
	
	/** The mapping context to use for Actions */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowedClasses="Input Mapping Context"))
	FSoftObjectPath DefaultMappingContext;
	/** The input class for Actions */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(DisplayName="Input Mapping Priority"))
	int32 MappingPriority;
	
	/** The input class for Actions */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(MetaClass="Enhanced Input Component Class"))
	FSoftClassPath InputComponentClass;

	/** The input class for Actions */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(DisplayName="Priority"))
	int32 InputPriority;

	/** The input class for Actions */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(DisplayName="Blocking"))
	bool InputBlocking;
	
	/** Actions to automatically add to controller */
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Actions", meta=(ExpandByDefault))
	TArray<TObjectPtr<UWHActionBase>> DefaultActions;
	

};
