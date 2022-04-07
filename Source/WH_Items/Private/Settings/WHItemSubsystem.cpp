/* Copyright © Noé Perard-Gayot 2022. */

#include "Settings/WHItemSubsystem.h"

#include "GameplayTagsManager.h"
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
		Settings->LoadDatable().BindUObject(this, &UWHItemSubsystem::GenerateItemList);
	}
}

void UWHItemSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UWHItemSubsystem::GenerateItemList()
{
	auto* const TagManager = UGameplayTagsManager::GetIfAllocated();
	if (const auto Settings = GetDefault<UWHItemSettings>())
	{
		if (const auto DTB = Settings->GetDatatable())
		{
			DTB->ForeachRow<FWHItemTableRow>(TEXT("UWHItemSubsystem::GenerateItemList"),[this,&TagManager]
			(const FName& Key, const FWHItemTableRow& Item)
			{
				if (const auto Class = Item.ItemClass.TryLoadClass<UWHItem>())
				{
					if (UWHItem* ItemPtr = NewObject<UWHItem>(this,Class, Key))
					{
						ItemDefaults.Add(ItemPtr);
						if (TagManager)
						{
							TagManager->AddNativeGameplayTag(Item.ItemTag.GetTagName(), FString("Item added tag"));
						}
					}
				}
			});
		}
	}
}
