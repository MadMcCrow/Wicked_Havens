// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WHAIController.generated.h"


/**
 *	Custom AI Controller allowing to use custom logic
 */
UCLASS( ClassGroup=(AI), Category="AI")
class WH_AI_API AWHAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWHAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnPossess(APawn* InPawn) override;

	virtual bool RunBehaviorTree(UBehaviorTree* BTAsset) override;

protected:

	/**
	 * The target location for this AI.
	 * The AI will then decide what to do about it (move, attack, etc )
	 */
	UPROPERTY(Transient,VisibleAnywhere, BlueprintReadWrite, Replicated, BlueprintGetter=GetTarget, BlueprintSetter=SetTarget, Category ="AI|Target")
	FVector Target;

public:

	UFUNCTION(BlueprintCallable, Category="AI")
	void SetTarget(const FVector& TargetLocation);


	UFUNCTION(BlueprintPure, Category = "AI")
	FVector GetTarget() const { return Target; }


public:

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;


};
