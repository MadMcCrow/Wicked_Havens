// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WHGameMode.generated.h"

/**
 *
 */
UCLASS()
class WICKED_HAVENS_API AWHGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AWHGameMode(const FObjectInitializer& ObjectInitializer);

private:

	/**
	 *	clan manager for this game
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHClanManagerComponent* ClanComponent;

public:

	static FName ClanComponentName;

};
