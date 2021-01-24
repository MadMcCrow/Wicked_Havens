// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WHPathMarker.h"

FName AWHPathMarker::BasePointsComponentName    = FName("BasePointsComponent");
FName AWHPathMarker::TurningPointsComponentName = FName("TurningPointsComponent");

// Sets default values
AWHPathMarker::AWHPathMarker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	BasePointsComponent    = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, BasePointsComponentName);
	TurningPointsComponent = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TurningPointsComponentName);
}

void AWHPathMarker::BeginPlay()
{
	Super::BeginPlay();

}

void AWHPathMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWHPathMarker::UpdatePath(FVector Start, FVector End)
{
}

