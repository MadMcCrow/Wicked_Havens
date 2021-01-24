// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WHBaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "WHAbilityCharacter.generated.h"

UCLASS()
class WICKED_HAVENS_API AWHAbilityCharacter : public AWHBaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWHAbilityCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:

	virtual void InitializeAttributes();

	/** Effect that initializes our default attributes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

private:

	/**
	 *	Attributes for this character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess))
	class UWHCharacterAttributeSet * Attributes;

	/**
	 *	Ability system for this character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess))
	class UWHAbilitySystemComponent* AbilitySystemComponent;

public:

	static FName AttributesName;
	static FName AbilitySystemComponentName;


};
