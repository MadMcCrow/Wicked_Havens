/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHAttributeContainer.h"
#include "WHAttributeComponent.generated.h"


/**
 *	@class UWHAttributeComponent
 *	@brief Stores and replicates attributes
 */
UCLASS(BlueprintType, MinimalAPI, ClassGroup=(WH), Category="Attributes", Meta = (BlueprintSpawnableComponent, DisplayName="Attributes Component"))
class UWHAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
	// CTR !
	UWHAttributeComponent();


protected:

	/** The attributes of this components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wicked Havens", Replicated)
	FWHAttributeContainer Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Wicked Havens", Replicated)
	UObject* TestInstanced;
};
