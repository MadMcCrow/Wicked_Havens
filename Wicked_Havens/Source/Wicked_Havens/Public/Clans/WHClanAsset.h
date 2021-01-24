// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "WHClanAsset.generated.h"


// forward declaration
class UWHClanAsset;

/**
 *  Diplomacy enum
 */
UENUM(BlueprintType, Category = "Clan")
enum class EWHClanDiplomacy : uint8
{
	Neutral		UMETA(DisplayName = "Neutral"),
	Ally		UMETA(DisplayName = "Ally"),
	Enemy		UMETA(DisplayName = "Enemy")
};


/**
 *  FWHClan
 */
USTRUCT(BlueprintType, Category = "Clan")
struct WICKED_HAVENS_API FWHClan
{
	GENERATED_BODY()
public:
	/**
	 *	Name as internal reference
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameID;


	/**
	 *	Name as displayed in game
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;


	/**
	 *	Extended description
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText Description;

};

/**
 *  FWHClanReference :
 *						Reference a clan as Ally or enemy
 */
USTRUCT(BlueprintType, Category = "Clan")
struct WICKED_HAVENS_API FWHClanReference : public FTableRowBase
{
	GENERATED_BODY()
public:

	/**
	 *	Name as displayed in game
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWHClanAsset> clan;

	/**
	 *	We only consider alignement to player for now
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	EWHClanDiplomacy Allignment = EWHClanDiplomacy::Enemy;

};

/**
 *
 */
UCLASS(BlueprintType, Category = "Clan")
class WICKED_HAVENS_API UWHClanAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, meta = (ShowOnlyInnerProperties))
	FWHClan Clan;


	UPROPERTY(EditDefaultsOnly, meta = (ShowOnlyInnerProperties))
	TArray<FWHClanReference> Alignments;

};
