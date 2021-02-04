// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WHPlayerController.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

AWHPlayerController::AWHPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
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
}

void AWHPlayerController::DeselectAICharacter(ACharacter* PlayerCharacter)
{
	SelectedCharacters.Remove(PlayerCharacter);
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

void AWHPlayerController::OnSelectTargetInput()
{
	const bool bIsRunning = ActionWasDoubleClicked(SelectTargetInputActionName);
	const FVector WorldPos = GetCursorWorldLocation();
	TArray<ACharacter*> SelectedChars;
	if (GetSelectedCharacters(SelectedChars))
	{
		for (ACharacter* CharItr : SelectedChars)
		{
			if (AAIController* AI = Cast<AAIController>(CharItr->GetController()))
			{
				AI->GetBlackboardComponent()->SetValueAsVector(TargetLocationKeyName, WorldPos);
				AI->GetBlackboardComponent()->SetValueAsBool(RunKeyName, bIsRunning);
			}
		}
	}
}
