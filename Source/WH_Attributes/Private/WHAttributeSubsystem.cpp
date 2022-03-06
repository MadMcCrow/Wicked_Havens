/* Copyright © Noé Perard-Gayot 2022. */

#include "WHAttributeSubsystem.h"
#include "Engine/DataTable.h"
#include "WHAttributeDefinition.h"
#include "WHAttributeSettings.h"

#if WITH_EDITOR
#include "UObject/ObjectSaveContext.h"
#endif // WITH_EDITOR

// Defined as Invalid Name :
const FName InvalidAttributeName = NAME_None;

UWHAttributeSubsystem::UWHAttributeSubsystem() : Super()
{
}

void UWHAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if WITH_EDITOR
	OnObjectPreSaveDelegate = FCoreUObjectDelegates::OnObjectPreSave.AddUObject(this, &UWHAttributeSubsystem::OnObjectPreSave);
	OnObjectPropertyChangedDelegate = FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &UWHAttributeSubsystem::OnObjectPropertyChanged);
	OnEnginePreExitDelegate = FCoreDelegates::OnEnginePreExit.AddUObject(this, &UWHAttributeSubsystem::OnEnginePreExit);
#endif //WITH_EDITOR
	// Make sure we'll be matching settings
	FCoreDelegates::OnFEngineLoopInitComplete.AddUObject(this, &UWHAttributeSubsystem::ImportSettings);
	ImportSettings();
}

void UWHAttributeSubsystem::Deinitialize()
{
	ExportSettings();
#if WITH_EDITOR
	FCoreUObjectDelegates::OnObjectPreSave.Remove(OnObjectPreSaveDelegate);
	FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(OnObjectPropertyChangedDelegate);
	FCoreDelegates::OnEnginePreExit.Remove(OnEnginePreExitDelegate);
#endif //WITH_EDITOR
	Super::Deinitialize();
}

bool UWHAttributeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWHAttributeSubsystem::ImportSettings()
{
	if (auto Settings = GetDefault<UWHAttributeSettings>())
	{
		// Update from saved settings
		GameAttributes = Settings->SavedGameAttributes;

		//Read our maps
		if (const auto DTB = Cast<UDataTable>(Settings->AttributesDataTable.TryLoad()))
		{
			DTB->ForeachRow<FWHAttributeDefinition>(TEXT("UWHAttributeSettings"),
				[this](const FName& RowName, const FWHAttributeDefinition& AttributeDefinition)
				{
					// Continue if Attribute ID already exist
					if (GameAttributes.FindKey(RowName))
					{
						return;
					}
					// TODO : Detect Renames:
					const auto GUID = FGuid::NewGuid();
					GameAttributes.Add(GUID, RowName);
				});
		}
	}

}

void UWHAttributeSubsystem::ExportSettings()
{
	if (const auto Settings = GetMutableDefault<UWHAttributeSettings>())
	{
		Settings->SavedGameAttributes = GameAttributes;
	}
}

FGuid UWHAttributeSubsystem::GetIDForName(const FName& Name)
{
	if (const auto UWHASS = Get())
	{
		if (const auto GUIDPtr = UWHASS->GameAttributes.FindKey(Name))
		{
			return *GUIDPtr;
		}
	}
	return FGuid();
}

const FName &UWHAttributeSubsystem::GetNameForID(const FGuid& GUID)
{
	if (const auto UWHASS = Get())
	{
		if (const auto NamePtr = UWHASS->GameAttributes.Find(GUID))
		{
			return *NamePtr;
		}
	}
	return InvalidAttributeName;
}

#if WITH_EDITOR
void UWHAttributeSubsystem::GetAllNames(TArray<FName>& OutNames)
{
	if (const auto UWHASS = Get())
	{
		UWHASS->GameAttributes.GenerateValueArray(OutNames);
	}
}

void UWHAttributeSubsystem::OnObjectPreSave(UObject* ModifiedObject, FObjectPreSaveContext Context)
{
	// avoid doing this when unnecessary:
	if (Context.IsCooking() || Context.IsProceduralSave())
	{
		return;
	}
	// make sure our datatable is the one being edited :
	if (ModifiedObject)
	{
		if (   ModifiedObject->IsA<UWHAttributeSettings>()
			|| ModifiedObject->IsA<UDataTable>())
		{
			ImportSettings();
			ExportSettings();
		}
	}
}

void UWHAttributeSubsystem::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	// make sure our datatable is the one being edited :
	if (Object)
	{
		if (   Object->IsA<UWHAttributeSettings>()
			|| Object->IsA<UDataTable>())
		{
			ImportSettings();
			ExportSettings();
		}
	}

}

void UWHAttributeSubsystem::OnEnginePreExit()
{
	ExportSettings();
}
#endif //WITH_EDITOR
