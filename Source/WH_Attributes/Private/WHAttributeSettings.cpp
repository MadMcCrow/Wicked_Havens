/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSettings.h"
#include "Engine/DataTable.h"
#include "WHAttributeDefinition.h"

UWHAttributeSettings::UWHAttributeSettings() : Super()
{
	if (auto DTB = Cast<UDataTable>(AttributesDataTable.TryLoad()))
	{
		DTB->ForeachRow<FWHAttributeDefinition>(TEXT("UWHAttributeSettings"),
			[this](const FName& RowName, const FWHAttributeDefinition& AttributeDefinition)
			{
				const auto GUID = FGuid::NewGuid(); // TODO : make sure we always get the same GUID
				PrivateAttributes.Add(GUID, RowName);
				ReversedPrivateAttributes.Add(RowName, GUID);
			});
	}
}

FGuid UWHAttributeSettings::GetIDForName(const FName& Name) const
{
	if (const auto GUIDPtr = ReversedPrivateAttributes.Find(Name))
	{
		return *GUIDPtr;
	}
	return FGuid();
}

FName UWHAttributeSettings::GetNameForID(const FGuid& GUID) const
{
	if (const auto NamePtr = PrivateAttributes.Find(GUID))
	{
		return *NamePtr;
	}
	return FName();
}

void UWHAttributeSettings::GetAllNames(TArray<FName>& OutNames) const
{
	PrivateAttributes.GenerateValueArray(OutNames);
}
