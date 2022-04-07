/* Copyright © Noé Perard-Gayot 2022. */

#pragma once


#include "Engine/DeveloperSettings.h"
#include "WHActionSettings.generated.h"


/**
 *	@class UWHActionSettings
 *	@brief Set all the parameters to have working Actions in Wicked Havens
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName=ItemSettings), Category="Wicked Havens|Actions", MinimalAPI)
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowedClasses="EnhancedInputComponent"))
	FSoftObjectPath DefaultMappingContext;
	
	/** The input class for Actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(MetaClass="EnhancedInputComponent"))
	FSoftClassPath InputComponentClass;

	/** The input class for Actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(DisplayName="Priority"))
	int32 InputPriority;

	/** The input class for Actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(DisplayName="Blocking"))
	bool InputBlocking;

	

};
