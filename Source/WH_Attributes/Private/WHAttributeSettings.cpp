/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSettings.h"
#include "WHAttributeSubsystem.h"

UWHAttributeSettings::UWHAttributeSettings() : Super()
{

}

#if WITH_EDITOR

void UWHAttributeSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd)
	{
		// New Attributes gets new IDs !
		for (auto & Itr : AttributeDefinitions)
		{
			if (Itr.UniqueID == FGuid()) // Invalid GUID
			{
				Itr.UniqueID = FGuid::NewGuid();
			}
		}
	}
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	// Update susystem !
	UWHAttributeSubsystem::Get()->ImportSettings();
}
#endif //WITH_EDITOR
