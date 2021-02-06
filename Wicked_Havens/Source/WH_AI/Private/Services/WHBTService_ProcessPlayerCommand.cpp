// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WHBTService_ProcessPlayerCommand.h"
#include "BehaviorTree/BlackboardComponent.h"

void UWHBTService_ProcessPlayerCommand::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
        if (BlackboardComp->GetValueAsObject(PlayerControllerKey.SelectedKeyName))
        {
            // We are controlled by player, all his commands should be ours.
            const FVector PlayerTargetLocation = BlackboardComp->GetValueAsVector(PlayerTargetLocationKey.SelectedKeyName);
            UObject* PlayerTargetObject  = BlackboardComp->GetValueAsObject(PlayerTargetActorKey.SelectedKeyName);
            BlackboardComp->SetValueAsVector(AITargetLocationKey.SelectedKeyName, PlayerTargetLocation);
            BlackboardComp->SetValueAsObject(AITargetActorKey.SelectedKeyName, PlayerTargetObject);
        }
    }
}