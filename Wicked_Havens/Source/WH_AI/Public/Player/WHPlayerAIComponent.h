// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WHPlayerAIComponent.generated.h"


UCLASS( ClassGroup=(AI), Category="AI", meta=(BlueprintSpawnableComponent), Within=PlayerController )
class WH_AI_API UWHPlayerAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWHPlayerAIComponent();

protected:
	
	virtual void BeginPlay() override;

	virtual void BindToInputComponent(class UInputComponent * InputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	FName SetTargetInputName;

private:

	UPROPERTY()
	FVector InputWorldLocation;

		
};
