// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHClanComponent.generated.h"


/**
 *
 */
UCLASS()
class WICKED_HAVENS_API UWHClanComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TSoftObjectPtr<class UWHClanAsset> Clan;


};
