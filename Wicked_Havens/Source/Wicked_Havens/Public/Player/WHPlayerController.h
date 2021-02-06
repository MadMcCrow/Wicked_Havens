// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Player/WHPlayerControllerBase.h"
#include "WHPlayerController.generated.h"

/**
 *
 */
UCLASS()
class WICKED_HAVENS_API AWHPlayerController : public AWHPlayerControllerBase
{
	GENERATED_BODY()

public:

	AWHPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	/**
	 *  @brief Add a character to the list of characters controlled by this Controller
	 *  Automatically selects the new character
	 */
	void ControlAICharacter(ACharacter * PlayerCharacter);

	/**
	 *  @brief remove a character from the list of characters controlled by this Controller
	 *  Automatically deselects the character
	 */
	void ReleaseAICharacter(ACharacter* PlayerCharacter);

	/**
	 *  @brief make this character receive orders from this controller
	 */
	void SelectAICharacter(ACharacter* PlayerCharacter);

	/**
	 *  @brief make this character receive orders from this controller
	 */
	void DeselectAICharacter(ACharacter* PlayerCharacter);

	/**
	 *  @brief get the characters that are "owned" by this controller
	 *  @return true if there's at least one character, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category="Character", meta = (HideSelfPin))
	UPARAM(DisplayName="HasValidCharacter") bool GetControlledCharacters(TArray<ACharacter*>& OutCharacters) const;

	/**
	 *  @brief get the characters that are currently selected by this controller
	 *  @return true if there's at least one character, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Character", meta=(HideSelfPin))
	UPARAM(DisplayName="HasValidCharacter") bool GetSelectedCharacters(TArray<ACharacter*>& OutCharacters) const;

	/**
	 *  @brief find out if this is one of our owns
	 *  @return true if this is in the Controlled Characters
	 */
	UFUNCTION(BlueprintPure, Category = "Character", meta=(HideSelfPin))
	UPARAM(DisplayName="IsControlled") bool IsCharacterControlled(ACharacter* Char) const;

	/**
	 *  @brief find out if this is one is Currently selected
	 *  @return true if this is in the selected Characters
	 */
	UFUNCTION(BlueprintPure, Category = "Character", meta=(HideSelfPin))
	UPARAM(DisplayName="IsSelected") bool IsCharacterSelected(ACharacter* Char) const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", DisplayName ="Select/Target Input" )
	FName SelectTargetInputActionName;

private:
	/**
	 *  SetDestination React to InputAction @see SelectTargetInputActionName
	 */
	UFUNCTION()
	void OnSelectTargetInput();

	// Reaction to target Input functions

	/** React to target being an Actor of the world */
	void OnTargetIsWorldActor(const FVector &Target, AActor* WorldActor = nullptr, bool bHaste =false);
	/** React to target being one of our characters */
	void OnTargetIsOwnedCharacter(ACharacter* Char, bool bDoubleClick =false);
	/** React to target being an other character    */
	void OnTargetIsOtherCharacter(ACharacter* Char, bool bHaste =false);

protected:
	/** Target Location Blackboard key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
	FName PlayerControllerKeyName;
	/** Target Location Blackboard key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
	FName PlayerTargetActorKeyName;
	/** Target Location Blackboard key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
	FName PlayerTargetLocationKeyName;
	/** Target Location Blackboard key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI|Blackboard")
	FName PlayerHasteBooleanKeyName;

private:
	/**
	 *  @brief Last selected player controlled character
	 */
	UPROPERTY(Transient)
	TArray<ACharacter*> SelectedCharacters;

	/**
	 *  @brief list of character this player controls
	 */
	UPROPERTY(Transient)
	TArray<ACharacter*> PlayerControlledCharacters;
};
