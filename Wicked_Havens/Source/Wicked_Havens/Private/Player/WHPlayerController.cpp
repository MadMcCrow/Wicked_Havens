// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WHPlayerController.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

AWHPlayerController::AWHPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AWHPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AWHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAction(SelectTargetInputActionName, EInputEvent::IE_Pressed, this, &AWHPlayerController::OnSelectTargetInput);
	}
}

void AWHPlayerController::ControlAICharacter(ACharacter* PlayerCharacter)
{
	PlayerControlledCharacters.AddUnique(PlayerCharacter);
	SelectAICharacter(PlayerCharacter);
}

void AWHPlayerController::ReleaseAICharacter(ACharacter* PlayerCharacter)
{
	DeselectAICharacter(PlayerCharacter);
	PlayerControlledCharacters.Remove(PlayerCharacter);
}

void AWHPlayerController::SelectAICharacter(ACharacter* PlayerCharacter)
{
	SelectedCharacters.AddUnique(PlayerCharacter);
	if (AAIController* AI = Cast<AAIController>(PlayerCharacter->GetController()))
	{
		if(UBlackboardComponent* BBComp = AI->GetBlackboardComponent())
			BBComp->SetValueAsObject(PlayerControllerKeyName, this);
	}
}

void AWHPlayerController::DeselectAICharacter(ACharacter* PlayerCharacter)
{
	SelectedCharacters.Remove(PlayerCharacter);
	if (AAIController* AI = Cast<AAIController>(PlayerCharacter->GetController()))
	{
		if(UBlackboardComponent* BBComp = AI->GetBlackboardComponent())
			BBComp->SetValueAsObject(PlayerControllerKeyName, nullptr);
	}
}

bool AWHPlayerController::GetControlledCharacters(TArray<ACharacter*>& OutCharacters) const
{
	OutCharacters.Reset();
	// is it necessary ? OutCharacters = PlayerControlledCharacters;
	OutCharacters = PlayerControlledCharacters.FilterByPredicate([](const ACharacter* CharItr) {return CharItr != nullptr; });
	return OutCharacters.Num() >= 1;
}

bool AWHPlayerController::GetSelectedCharacters(TArray<ACharacter*>& OutCharacters) const
{
	OutCharacters.Reset();
	// is it necessary ? OutCharacters = PlayerControlledCharacters;
	OutCharacters = SelectedCharacters.FilterByPredicate([](const ACharacter* CharItr) {return CharItr != nullptr; });
	return OutCharacters.Num() >= 1;
}

bool AWHPlayerController::IsCharacterControlled(ACharacter* Char) const
{
	TArray<ACharacter*> ControlledChars;
	if (GetControlledCharacters(ControlledChars))
	{
		return ControlledChars.Contains(Char);
	}
	return false;
}

bool AWHPlayerController::IsCharacterSelected(ACharacter* Char) const
{
	TArray<ACharacter*> SelectedChars;
	if (GetSelectedCharacters(SelectedChars))
	{
		return SelectedChars.Contains(Char);
	}
	return false;
}

void AWHPlayerController::OnSelectTargetInput()
{
	const bool bIsDoubleClick = ActionWasDoubleClicked(SelectTargetInputActionName);
	FVector WorldLocation;
	AActor* TargetActor;
	GetCursorWorldTarget(WorldLocation, TargetActor);
	if (ACharacter* TargetChar = Cast<ACharacter>(TargetActor))
	{
		if (IsCharacterControlled(TargetChar))
		{
			OnTargetIsOwnedCharacter(TargetChar,bIsDoubleClick );
			return;
		}
		OnTargetIsOtherCharacter(TargetChar,bIsDoubleClick );
		return;
	}
	OnTargetIsWorldActor(WorldLocation,TargetActor, bIsDoubleClick);
	
}

void AWHPlayerController::OnTargetIsWorldActor(const FVector &Target, AActor* WorldActor, bool bHaste)
{
	TArray<ACharacter*> SelectedChars;
	if (GetSelectedCharacters(SelectedChars))
	{
		for (ACharacter* CharItr : SelectedChars)
		{
			if (AAIController* AI = Cast<AAIController>(CharItr->GetController()))
			{
				if(UBlackboardComponent* BB = AI->GetBlackboardComponent())
				{
					// make sure we are the controller
					BB->SetValueAsObject(PlayerControllerKeyName, this);
					// give all infos about us
					BB->SetValueAsVector(PlayerTargetLocationKeyName, Target);
					BB->SetValueAsObject(PlayerTargetActorKeyName, WorldActor);
					BB->SetValueAsBool(PlayerHasteBooleanKeyName, bHaste);
				}
			}
		}
	}
}

void AWHPlayerController::OnTargetIsOwnedCharacter(ACharacter* Char, bool bDoubleClick)
{
	if (!bDoubleClick)
	{
		if (IsCharacterSelected(Char))
		{
			DeselectAICharacter(Char);
		}
		else
		{
			SelectAICharacter(Char);
		}
	}
}

void AWHPlayerController::OnTargetIsOtherCharacter(ACharacter* Char, bool bHaste)
{

}