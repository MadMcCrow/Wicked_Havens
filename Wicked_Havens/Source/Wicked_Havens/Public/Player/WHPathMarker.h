// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WHPathMarker.generated.h"

UCLASS()
class WICKED_HAVENS_API AWHPathMarker : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWHPathMarker(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 *	 the points in straight lines
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UInstancedStaticMeshComponent* BasePointsComponent;

	/**
	 *	 the points where a clear turn is done
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	class UInstancedStaticMeshComponent* TurningPointsComponent;
public:

	static FName BasePointsComponentName;
	static FName TurningPointsComponentName;

public:

	UFUNCTION()
	void UpdatePath(FVector Start, FVector End);


};
