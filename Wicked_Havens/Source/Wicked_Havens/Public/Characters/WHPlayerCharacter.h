// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WHBaseCharacter.h"
#include "WHPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class WICKED_HAVENS_API AWHPlayerCharacter : public AWHBaseCharacter
{
	GENERATED_BODY()
public:

	AWHPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

protected:

	//UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	//class AWHPlayerController* PlayerController;

	UPROPERTY(SaveGame, DuplicateTransient, EditAnywhere, BlueprintReadOnly)
	FName CharacterName;

};
