/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "CoreMinimal.h"
#include "Actions/WHActionBase.h"
#include "WHCharacterAction.generated.h"


/**
 *	@class UWHCharacterAction
 *	What to do on an Action (input or other)
 *	@todo
 *		- maybe make this a ActorComponent
 *		- Set what animation state or whatever to play
 */
UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew, ClassGroup=(WH), Category = "Wicked Havens|Character")
class UWHCharacterAction : public UWHActionBase
{
	GENERATED_BODY()
	friend class AWHCharacterBase;

public:
	// CTR
	UWHCharacterAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** Get Associated Character */
	UFUNCTION(BlueprintPure, Category="Action")
	AWHCharacterBase* GetActingCharacter() const;

protected:
	
	/** will call add movement input on owning character */
	virtual void AddMovementInput(const FVector& Vector);
	
};
