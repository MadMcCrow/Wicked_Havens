/* Copyright © Noé Perard-Gayot 2021. */

#pragma once

#include "Engine/DataAsset.h"
#include "WHCharacterData.generated.h"


class USkeletalMesh;

/**
 *	UWHCharacterData
 * 	@brief Class to contain info about a character
 */
UCLASS()
class WICKED_HAVENS_API UWHCharacterData : public UDataAsset
{
	GENERATED_BODY()

protected:

	/**
	 * 	Name for that specific character
	 */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Base")
	FText DisplayName;

	/**
	 * 	Description : Lore info
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Base")
	FText Description;

	/**
	 * 	Mesh : the Mesh to use
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Visual")
	TSoftObjectPtr<USkeletalMesh> Mesh;


public :

	FORCEINLINE USkeletalMesh* GetMesh() const {return Mesh.Get();}


};
