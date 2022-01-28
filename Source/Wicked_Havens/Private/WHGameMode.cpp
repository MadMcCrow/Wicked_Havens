/* Copyright © Noé Perard-Gayot 2021. */

#include "WHGameMode.h"
#include "GameFramework/Character.h"

AWHGameMode::AWHGameMode(const FObjectInitializer& ObjectInitializer)
{

}

void AWHGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
}

ACharacter* AWHGameMode::SpawnPlayerCharacter(APlayerController* Player)
{
	// Set spawn infos
	AActor* StartSpot = FindPlayerStart(Player);
	FRotator StartRotation(ForceInit);
	StartRotation.Yaw = StartSpot->GetActorRotation().Yaw;
	const FVector StartLocation = StartSpot->GetActorLocation();
	const FTransform Transform = FTransform(StartRotation, StartLocation);

	// otherwise spawn it
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	UClass* PawnClass = PlayerCharacterClass;
	// Spawn character
	ACharacter* ResultPawn = GetWorld()->SpawnActor<ACharacter>(PawnClass, Transform, SpawnInfo);
#if !UE_BUILD_SHIPPING
	if (!ResultPawn)
		UE_LOG(LogGameMode, Warning, TEXT("SpawnPlayerCharacter: Couldn't spawn Pawn of type %s at %s"), *GetNameSafe(PawnClass), *Transform.ToHumanReadableString());
#endif // !UE_BUILD_SHIPPING

	return ResultPawn;
}
