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
	// Empty our maps before :
	PrivateAttributes.Empty();
	ReversedPrivateAttributes.Empty();

	//Read our maps
	if (auto DTB = Cast<UDataTable>(AttributesDataTable.TryLoad()))
	{
		DTB->ForeachRow<FWHAttributeDefinition>(TEXT("UWHAttributeSettings"),
			[this](const FName& RowName, const FWHAttributeDefinition& AttributeDefinition)
			{
				const auto GUID = GetGUIDForEntry(RowName, AttributeDefinition);
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

#if WITH_EDITOR
void UWHAttributeSettings::GetAllNames(TArray<FName>& OutNames) const
{
	if (const auto Settings = GetMutableDefault<UWHAttributeSettings>())
		Settings->Initialize();
	PrivateAttributes.GenerateValueArray(OutNames);
}


void UWHAttributeSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	Initialize();
}

void UWHAttributeSettings::PostInitProperties()
{
	Super::PostInitProperties();
	OnObjectPreSaveDelegate = FCoreUObjectDelegates::OnObjectPreSave.AddUObject(this, &UWHAttributeSettings::OnObjectPreSave);
	Initialize();
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

FGuid UWHAttributeSettings::GetGUIDForEntry(const FName EntryName, const FWHAttributeDefinition& Definition) const
{
	if (auto DTB = Cast<UDataTable>(AttributesDataTable.TryLoad()))
	{
		FGuid Retval = FGuid::NewGuid();
		Retval.A = DTB->GetRowNames().Find(EntryName);
		return Retval;
	}
	return FGuid::NewGuid();// TODO : make sure we always get the same GUID
}
