/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WHAttributeSettings.generated.h"


/**
 *	@class UWHItemSettings
 *	@brief A simple way to set @see UWHItemSubsystem Items.
 */
UCLASS(ClassGroup=(WH), config=Game, meta=(DisplayName=AttributeSettings), Category="Attributes", MinimalAPI)
class UWHAttributeSettings : public UDeveloperSettings
{
    GENERATED_BODY()


public:

	/**	Get the attributes as UEnum	 */
	UEnum* GetAttributeEnum() const;

	int64 GetValueForName(const FName& InName) const;
	FName GetNameForValue(const int64& InValue) const;

protected:

    /**
     *	An enum containing all the different attributes to use in Wicked Havens
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowedClasses="Enum"))
    FSoftObjectPath AttributesEnum;


};
