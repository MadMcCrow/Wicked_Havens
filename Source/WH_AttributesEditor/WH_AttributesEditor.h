/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

/**
 *	We need a module interface to have our customization of attributes
 */
class WH_ATTRIBUTESEDITOR_API FWH_AttributesEditor : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FWHAttributeNamePinFactory> WHAttributeNamePinFactory;

};
