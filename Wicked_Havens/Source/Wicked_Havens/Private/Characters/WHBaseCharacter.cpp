// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WHBaseCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/Components/WHAttributesComponent.h"
#include "Characters/Components/WHClanComponent.h"
#include "Characters/Components/WHFightComponent.h"
#include "Characters/Components/WHPathComponent.h"

FName AWHBaseCharacter::ClanComponentName = FName("ClanComponent");
FName AWHBaseCharacter::FightComponentName  = FName("FightComponent");
FName AWHBaseCharacter::PathComponentName = FName("PathComponent");

// Sets default values
AWHBaseCharacter::AWHBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	// Components
	ClanComponent = ObjectInitializer.CreateDefaultSubobject<UWHClanComponent>(this,ClanComponentName);
	FightComponent = ObjectInitializer.CreateDefaultSubobject<UWHFightComponent>(this, FightComponentName);
	PathComponent = ObjectInitializer.CreateDefaultSubobject<UWHPathComponent>(this, PathComponentName);

	ClanComponent->SetIsReplicated(true);
	FightComponent->SetIsReplicated(true);
	PathComponent->SetIsReplicated(false); // do not replicate path, please;

	// Ignore controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AWHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UBehaviorTree* Behaviour = BehaviourTree.Get())
	{

		if (AAIController* AI  = Cast<AAIController>(GetController()))
		{
			UBlackboardComponent * BBComp = AI->GetBlackboardComponent();
			AI->UseBlackboard(Behaviour->GetBlackboardAsset(), BBComp);
			AI->RunBehaviorTree(Behaviour);
		}

	}
}