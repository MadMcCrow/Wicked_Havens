/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Actions/WHActionBase.h"
#include "WHCharacterAction.generated.h"

class AWHCharacterBase;

/**
 *	@class UWHCharacterAction
 *	Add functionnality to command a Character instead 
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew, ClassGroup=(WH), Category = "Wicked Havens|Character")
class UWHCharacterAction : public UWHActionBase
{
	GENERATED_BODY()

public:
	
	/** Get Associated Character */
	UFUNCTION(BlueprintPure, Category="Action")
	AWHCharacterBase* GetActingCharacter() const;

protected:
	
	/** will call add movement input on owning character */
	virtual void AddMovementInput(const FVector& Vector);
	
};
