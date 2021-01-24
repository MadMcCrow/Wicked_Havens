// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WHBaseCharacter.h"

// Sets default values
AWHBaseCharacter::AWHBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWHBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWHBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWHBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

