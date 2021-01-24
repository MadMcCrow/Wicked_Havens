// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WHPlayerController.generated.h"

/**
 *	Base Player controller for Wicked Havens
 */
UCLASS()
class WICKED_HAVENS_API AWHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AWHPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void SetupInputComponent() override;

private:

	/**
	 *	component that draws your orders to the AI controller
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHPathComponent* PathComponent;

	/**
	 *	component that tells your AI what to do
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UWHPlayerAIComponent* AIComponent;

public:

	static FName PathComponentName;
	static FName AIComponentName;

protected:

	/**
	 * ActionName for click in the world
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	FName SetDestinationActionName;

	/**
	 * do we move on press, release or double click
	 * @todo: move to a smart rebind system
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EInputEvent> SetDestinationActionMode;

private:

	// just pass info to component
	UFUNCTION()
	void SetDestination();
};
