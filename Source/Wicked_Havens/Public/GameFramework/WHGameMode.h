/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "GameFramework/GameMode.h"
#include "WHGameMode.generated.h"

class AWHCharacterBase;

/**
 *	Game Mode for Wicked Havens
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
	TSubclassOf<AWHCharacterBase> PlayerCharacterClass;

private:

	/**
	 *  Spawn and set player character either from save or use default
	 *  @param Player			The player you want to add a character to
	 */
	UFUNCTION()
	AWHCharacterBase* SpawnPlayerCharacter(class APlayerController* Player);


};
