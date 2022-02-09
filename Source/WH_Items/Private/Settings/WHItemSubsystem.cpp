/* Copyright © Noé Perard-Gayot 2022. */

#include "Settings/WHItemSubsystem.h"
#include "Engine/DataTable.h"
#include "Items/WHItem.h"
#include "Items/WHItemTableRow.h"
#include "Settings/WHItemSettings.h"

UWHItemSubsystem* UWHItemSubsystem::Get()
{
	const auto GI = GEngine->GetWorld()->GetGameInstance();
	return GI->GetSubsystem<UWHItemSubsystem>();
}

void UWHItemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (const auto Settings = GetDefault<UWHItemSettings>())
	{
		Settings->LoadDatable().BindRaw(this, &UWHItemSubsystem::GenerateItemList);
	}
}

void UWHItemSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UWHItemSubsystem::GenerateItemList()
{
	if (const auto Settings = GetDefault<UWHItemSettings>())
	{
		if (const auto DTB = Settings->GetDatatable())
		{
			DTB->ForeachRow<FWHItemTableRow>(TEXT("UWHItemSubsystem::GenerateItemList"),[this,&Settings,DTB]
			(const FName& Key, const FWHItemTableRow& Item)
			{
				if (const auto Class = Item.ItemClass.TryLoadClass<UWHItem>())
				{
					UWHItem* ItemPtr = NewObject<UWHItem>(this,Class, Key);
					if (ItemPtr)
					{
						ItemPtr->ItemHandle.DataTable = DTB;
						ItemPtr->ItemHandle.RowName   = Key;
						Items.Add(ItemPtr);
					}
				}
			});
		}
	}
}
