// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHPathComponent.generated.h"

/**
 *	Simple component to draw path for orders
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WICKED_HAVENS_API UWHPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWHPathComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetDestination();


};
