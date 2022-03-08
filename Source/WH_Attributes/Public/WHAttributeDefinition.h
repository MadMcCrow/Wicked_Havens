/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "WHAttributeType.h"
#include "Engine/DataTable.h"
#include "WHAttributeDefinition.generated.h"


/**
 *	A table row to define an attribute
 *	RowName is attribute HumanFriendlyName(TM)
 */
USTRUCT(Category="Attributes")
struct FWHAttributeDefinition : public FTableRowBase
{
	GENERATED_BODY()

	/**	Used both in game and in editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

#if WITH_EDITORONLY_DATA
	/**	Just a comment there, will not even be readable in the final game so don't bother too much */
	UPROPERTY(EditAnywhere)
	FString DeveloperComment;
#endif //WITH_EDITORONLY_DATA

	/**	Attribute Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWHAttributeType Type;

};
