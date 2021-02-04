// Fill out your copyright notice in the Description page of Project Settings.

#include "Controller/WHAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DemoNetDriver.h"


AWHAIController::AWHAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
}

void AWHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}


bool AWHAIController::RunBehaviorTree(UBehaviorTree* BTAsset)
{
	return Super::RunBehaviorTree(BTAsset);

}

void AWHAIController::SetTarget(const FVector& TargetLocation)
{
	if (HasAuthority())
	{
		Target = TargetLocation;
	}
}


void AWHAIController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWHAIController, Target);
}
