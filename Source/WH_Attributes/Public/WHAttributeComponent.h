/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHAttributeContainer.h"
#include "WHAttributeComponent.generated.h"


/**
 *	@class UWHAttributeSettings
 *	@brief Store and helps generate all the attribute names and GUIDs
 */
UCLASS(BlueprintType, MinimalAPI, ClassGroup=(WH), Category="Attributes", Meta = (BlueprintSpawnableComponent, DisplayName="Attributes Component"))
class UWHAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
	// CTR !
	UWHAttributeComponent();

	/** Getter for a certain attribute */
	UFUNCTION(BlueprintPure, Category = "Wicked Havens|Attributes")
	WH_ATTRIBUTES_API FWHAttributeValue GetAttributeValue(const FWHAttributeName& Name) const;

	/** Setter for a certain attribute */
	UFUNCTION(BlueprintPure, Category = "Wicked Havens|Attributes")
	WH_ATTRIBUTES_API void SetAttributeValue(const FWHAttributeName& Name, const FWHAttributeValue& NewValue) const;

protected:

	/** The attributes of this components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wicked Havens", Replicated)
	FWHAttributeContainer Attributes;

};
