/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "GameFramework/GameMode.h"
#include "WHGameMode.generated.h"

/**
 *
 */
UCLASS()
class WICKED_HAVENS_API AWHGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AWHGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;

protected:

	/** The class of PlayerController to spawn for players logging in. */
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<ACharacter> PlayerCharacterClass;

private:

	/**
	 *  Spawn and set player character either from save or use default
	 *  @param Player			The player you want to add a character to
	 *  @todo  Implement character save system.
	 */
	ACharacter* SpawnPlayerCharacter(class APlayerController* Player);


};
