/* Copyright © Noé Perard-Gayot 2022. */

#include "GameFramework/WHPlayerController.h"
#include "WHCharacterBase.h"
#include "Net/UnrealNetwork.h"


AWHPlayerController::AWHPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ActiveActionPawn = INDEX_NONE;
}

int32 AWHPlayerController::AddActionCharacter(AWHCharacterBase* WHCharacter, int32 DesiredIndex)
{
	if (WHCharacter)
	{
		const int32 RealIndex = FMath::Min(ActionCharacters.Num(), DesiredIndex);
		ActionCharacters.Insert(WHCharacter, RealIndex);
		if (ActiveActionPawn == INDEX_NONE)
		{
			SetActiveActionCharacter(RealIndex);
		}
		return RealIndex;
	}
	return INDEX_NONE;
}

AWHCharacterBase* AWHPlayerController::SetActiveActionCharacter(int32 Index)
{
	if (ActionCharacters.IsValidIndex(Index))
	{
		ActiveActionPawn = Index;
		return ActionCharacters[ActiveActionPawn];
	}
	return nullptr;
}

AWHCharacterBase* AWHPlayerController::GetActiveActionCharacter() const
{
	if (ActionCharacters.IsValidIndex(ActiveActionPawn))
	{
		return ActionCharacters[ActiveActionPawn];
	}
	return nullptr;
}

void AWHPlayerController::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWHPlayerController, ActionCharacters);
	DOREPLIFETIME(AWHPlayerController, ActiveActionPawn);
}
