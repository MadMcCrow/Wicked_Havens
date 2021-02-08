// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WHAILibrary.generated.h"

/**
 *		Different type of action an AI can perform
 */
UENUM(BlueprintType)
enum class EAIAction : uint8
{
	None    UMETA(DisplayName = "None"),
	Attack  UMETA(DisplayName = "Attack"),
	Move    UMETA(DisplayName = "Move"),
	Talk    UMETA(DisplayName = "Talk"),
	Max		UMETA(Hidden),
};

/**
 *		Static functions to help other module with the AI system
 */
UCLASS()
class WH_AI_API UWHAILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 *	Get AI reaction to target
	 *	@param Target : The world Position we consider for targeting
	 *	@return What the AI will do if tasked to interact with Target
	 */
	UFUNCTION(BlueprintCallable)
	static EAIAction GetActionForTarget(FVector Target);

	/**
	 *	Ask Player AI to do something for Target
	 *	@param Target : The world Position we consider for targeting
	 *	@return true if the order can be completed
	 */
	UFUNCTION(BlueprintCallable, Category="AI" )
	static bool SetTargetForPlayerAI(FVector Target);

	/**
	 *	GetUserControlledAIController
	 *	@return The one AI controller the Player is giving order to.
	 */
	UFUNCTION(BlueprintCallable, Category="AI" )
	static class AWHAIController* GetUserControlledAIController();

};