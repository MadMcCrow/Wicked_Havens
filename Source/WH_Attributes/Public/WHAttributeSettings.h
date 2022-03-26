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

};
