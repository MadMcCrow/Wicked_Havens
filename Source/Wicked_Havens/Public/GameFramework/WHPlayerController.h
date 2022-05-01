/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "GameFramework/PlayerController.h"
#include "WHPlayerController.generated.h"

class AWHCharacterBase;

/**
 *
 */
UCLASS()
class WICKED_HAVENS_API AWHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// CTR
	AWHPlayerController(const FObjectInitializer& ObjectInitializer);

	/**
	 *	AddActionCharacter
	 *	@param WHCharacter		the pawn we will be controlling
	 *	@param DesiredIndex		how up the stack should it be ?
	 *	@return					the real index of this new pawn 
	 *	the camera pawn is not in this list.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Wicked Havens")
	virtual int32 AddActionCharacter(AWHCharacterBase* WHCharacter, int32 DesiredIndex = -1);

	/**
	 *	SetActiveActionCharacter
	 *	@param Index			the index you wanna make active
	 *	@return					the pawn you want to control
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Wicked Havens")
	virtual AWHCharacterBase* SetActiveActionCharacter(int32 Index = 0);

	/**
	 *	GetActiveActionCharacter
	 *	@return					the pawn currently controlled
	 */
	UFUNCTION(BlueprintPure, Category="Wicked Havens")
	AWHCharacterBase* GetActiveActionCharacter() const;
	
private:

	/** the Pawns we control via our actions */
	UPROPERTY(Replicated)
	TArray<AWHCharacterBase*> ActionCharacters;

	/** wich one should be considered active right now */
	UPROPERTY(Replicated)
	int32	ActiveActionPawn;
	
};
