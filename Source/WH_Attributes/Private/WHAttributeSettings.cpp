/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSettings.h"
#include "Engine/DataTable.h"
#include "WHAttributeDefinition.h"

#if WITH_EDITOR
#include "UObject/ObjectSaveContext.h"
#endif // WITH_EDITOR

UWHAttributeSettings::UWHAttributeSettings() : Super()
{
	Initialize();
}

void UWHAttributeSettings::Initialize()
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

#if WITH_EDITOR
void UWHAttributeSettings::PostInitProperties()
{
	Super::PostInitProperties();
	Initialize();
	OnObjectPreSaveDelegate = FCoreUObjectDelegates::OnObjectPreSave.AddUObject(this, &UWHAttributeSettings::OnObjectPreSave);
}

void UWHAttributeSettings::OnObjectPreSave(UObject* ModifiedObject, FObjectPreSaveContext Context)
{
	// avoid doing this when unnecessary:
	if (Context.IsCooking() || Context.IsProceduralSave())
	{
		return;
	}
	// make sure our datatable is the one being edited :
	if (ModifiedObject && ModifiedObject->IsA<UDataTable>())
	{
		// Only update the defaults (is it us ? I don't care)
		if (const auto Settings = GetMutableDefault<UWHAttributeSettings>())
		{
			if (Settings->AttributesDataTable == FSoftObjectPath(ModifiedObject))
			{
				Settings->Initialize();
			}
		}
	}
}
#endif //WITH_EDITOR
