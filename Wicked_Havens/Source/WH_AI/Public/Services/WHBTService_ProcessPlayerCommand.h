// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WHBTService_ProcessPlayerCommand.generated.h"

/**
 * 	Simple process to check different Blackboard keys and set others
 * 	Try to see if you're currently controlled by player, and if so use it's targets to set our targets
 */
UCLASS(ClassGroup=AI, Category="AI")
class WH_AI_API UWHBTService_ProcessPlayerCommand : public UBTService
{
	GENERATED_BODY()

private:
	/**
	 * 	 Player Controller Object Key
	 *   Simple key to know if a player is currently controlling us
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(OnlyShowInnerProperties, AllowPrivateAccess))
	FBlackboardKeySelector PlayerControllerKey;

	/**
	 * 	 Player Controller Target Vector Key
	 *   Simple key to know where the player set our target last
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(OnlyShowInnerProperties, AllowPrivateAccess))
	FBlackboardKeySelector PlayerTargetLocationKey;

	/**
	 * 	 Player Controller Target Object Key
	 *   Simple key to know what the player set our target last
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(OnlyShowInnerProperties, AllowPrivateAccess))
	FBlackboardKeySelector PlayerTargetActorKey;

	/**
	 * 	 AI Vector Key
	 *   Where do we store our targets
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(OnlyShowInnerProperties, AllowPrivateAccess))
	FBlackboardKeySelector AITargetLocationKey;

	/**
	 * 	 AI Object Key
	 *   Where do we store our targets
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(OnlyShowInnerProperties, AllowPrivateAccess))
	FBlackboardKeySelector AITargetActorKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
