/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Items/WHItemTableRow.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WHItemSubsystem.generated.h"


/**
 * @class UWHItemSubsystem
 * @brief The subsystem responsible for referencing all items
 */
UCLASS(ClassGroup=(WH))
class UWHItemSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:

	static UWHItemSubsystem* Get();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;



protected:
	void GenerateItemList();

private:

	/**
	 *	Set of all items ever spawned
	 */
	UPROPERTY()
	TSet<TObjectPtr<class UWHItem>> ItemDefaults;
};
