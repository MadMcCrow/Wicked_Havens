// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WHBaseCharacter.generated.h"

UCLASS()
class WICKED_HAVENS_API AWHBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWHBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;


protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	TSoftObjectPtr<class UBehaviorTree> BehaviourTree;

private:

	/**
	 *	Clan for this character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHClanComponent* ClanComponent;

	/**
	 *	Fight System for this character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHFightComponent* FightComponent;

	/**
	 *	PathComponent : system to show where this character is going
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHPathComponent* PathComponent;


public:

	static FName ClanComponentName;
	static FName FightComponentName;
	static FName PathComponentName;

};
