/* Copyright © Noé Perard-Gayot 2022. */

#include "System/WHActionSettings.h"
#include "EnhancedInputComponent.h"

UWHActionSettings::UWHActionSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, InputComponentClass(UEnhancedInputComponent::StaticClass())
, InputPriority(0)
, InputBlocking(true)
{
}
