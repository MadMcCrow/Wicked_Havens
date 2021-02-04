// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WHAttributesComponent.h"
#include "WHFightComponent.generated.h"

/**
 *	Handle all fight related elements for this character
 */
UCLASS( ClassGroup=(Character), meta=(BlueprintSpawnableComponent) )
class WICKED_HAVENS_API UWHFightComponent : public UWHAttributesComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWHFightComponent();

private:

	//UPROPERTY(Transient)



public:
	UFUNCTION(BlueprintPure, Category = "Fight")
	virtual bool IsInRange(const AActor* Target) const;


};
