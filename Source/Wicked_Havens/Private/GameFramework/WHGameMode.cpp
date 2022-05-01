/* Copyright © Noé Perard-Gayot 2022. */

#include "GameFramework/WHGameMode.h"

#include "WHCharacterBase.h"
#include "Camera/WHPlayerCamera.h"
#include "GameFramework/Character.h"
#include "GameFramework/WHPlayerController.h"

AWHGameMode::AWHGameMode(const FObjectInitializer& ObjectInitializer)
{
	PlayerControllerClass	= AWHPlayerController::StaticClass();
	DefaultPawnClass		= AWHPlayerCamera::StaticClass();
	SpectatorClass			= AWHPlayerCamera::StaticClass();
}

void AWHGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);

	// for now we just spawn a character :
	// In the long run, we'll show the player a menu to select a new character, or check if he has a save
	if (const auto PlayerController = Cast<AWHPlayerController>(NewPlayer))
	{
		const auto Pawn = SpawnPlayerCharacter(PlayerController);
		PlayerController->AddActionCharacter(Pawn);
	}
	
}

AWHCharacterBase* AWHGameMode::SpawnPlayerCharacter(APlayerController* Player)
{
	// Set spawn infos
	AActor* StartSpot = FindPlayerStart(Player);
	FRotator StartRotation(ForceInit);
	StartRotation.Yaw = StartSpot->GetActorRotation().Yaw;
	const FVector StartLocation = StartSpot->GetActorLocation();
	const FTransform Transform = FTransform(StartRotation, StartLocation);
	// Prepare spawn
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	UClass* PawnClass = PlayerCharacterClass;
	// Spawn character
	AWHCharacterBase* ResultPawn = GetWorld()->SpawnActor<AWHCharacterBase>(PawnClass, Transform, SpawnInfo);
	return ResultPawn;
}
