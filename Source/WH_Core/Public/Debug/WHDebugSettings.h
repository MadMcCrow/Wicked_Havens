/* Copyright © Noé Perard-Gayot 2022. */

#pragma once


#include "Engine/DeveloperSettings.h"
#include "WHDebugSettings.generated.h"


/**
 *	@class UWHDebugSettings
 *	@brief Set all the parameters to have working Actions in Wicked Havens
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName=Debug), Category="Wicked Havens|Debug", MinimalAPI)
class UWHDebugSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	friend class UWHActionSubsystem;

public:
	
	// Category override :
	virtual FName GetCategoryName() const override {return FName("Wicked Havens");}
	
protected:
	

};
