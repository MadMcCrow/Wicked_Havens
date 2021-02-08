// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHClanManagerComponent.generated.h"


/**
 *
 */
UCLASS(Within=WHGameMode)
class WICKED_HAVENS_API UWHClanManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<TSoftObjectPtr<class UWHClanAsset>> Clans;

};
