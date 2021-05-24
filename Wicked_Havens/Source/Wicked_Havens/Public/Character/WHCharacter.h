// Copyright © Noé Perard-Gayot 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WHCharacter.generated.h"


class UWHCharacterData;

UCLASS()
class WICKED_HAVENS_API AWHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWHCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Customisation Data to use
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wicked Havens", DisplayName = "Character Customisation")
	TSoftObjectPtr<UWHCharacterData> CharData;

	/**
	 * Apply stored information to this character
	 */
	virtual void ApplyCharacterData() const;

	/**
	 * 	Apply Extra effect on Character in Blueprint
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Wicked Havens")
	void ApplyCharacterData_BP(const UWHCharacterData * Data) const;

	/**
	 *	Change character data - will check first if data is valid
	 */
	UFUNCTION(BlueprintCallable, Category = "Wicked Havens")
	void SetCharacterData(const TSoftObjectPtr<UWHCharacterData> &NewCharData);

	/**
	 * 	Will load Character data, So that we can use it
	 * 	@todo : implement async-loading and deferred spawning
	 */
	void LoadCharacterData() const;
};
