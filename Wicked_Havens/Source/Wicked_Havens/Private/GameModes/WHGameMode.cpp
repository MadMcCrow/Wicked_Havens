// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/WHGameMode.h"
#include "Clans/WHClanManagerComponent.h"
#include "Player/WHPlayerController.h"

FName AWHGameMode::ClanComponentName = "ClanComponent";

AWHGameMode::AWHGameMode(const FObjectInitializer& ObjectInitializer)
{
	// Create clan component
	ClanComponent = ObjectInitializer.CreateDefaultSubobject<UWHClanManagerComponent>(this, ClanComponentName);
}

void AWHGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
	if (AWHPlayerController * PC = Cast<AWHPlayerController>(NewPlayer))
	{
		if(ACharacter* Character = SpawnPlayerCharacter(PC))
		{
			PC->ControlAICharacter(Character);
		}
	}
}

ACharacter* AWHGameMode::SpawnPlayerCharacter(AWHPlayerController* Player)
{
	// Set spawn infos
	AActor* StartSpot = FindPlayerStart(Player);
	FRotator StartRotation(ForceInit);
	StartRotation.Yaw = StartSpot->GetActorRotation().Yaw;
	const FVector StartLocation = StartSpot->GetActorLocation();
	const FTransform Transform = FTransform(StartRotation, StartLocation);

	// if there's an already spawned character, use it
	TArray<ACharacter*> AlreadySpawnedChars;
	if (Player->GetControlledCharacters(AlreadySpawnedChars))
	{
		ACharacter*  PreviousChar = AlreadySpawnedChars[0];
		PreviousChar->SetActorTransform(Transform);
		return PreviousChar;
	}

	// otherwise spawn it
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	UClass* PawnClass = PlayerCharacterClass;
	// Spawn character
	AWHPlayerCharacter* ResultPawn = GetWorld()->SpawnActor<AWHPlayerCharacter>(PawnClass, Transform, SpawnInfo);
#if !UE_BUILD_SHIPPING
	if (!ResultPawn)
		UE_LOG(LogGameMode, Warning, TEXT("SpawnPlayerCharacter: Couldn't spawn Pawn of type %s at %s"), *GetNameSafe(PawnClass), *Transform.ToHumanReadableString());
#endif // !UE_BUILD_SHIPPING

	return ResultPawn;
}