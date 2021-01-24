// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/WHGameMode.h"
#include "Clans/WHClanManagerComponent.h"

FName AWHGameMode::ClanComponentName = "ClanComponent";

AWHGameMode::AWHGameMode(const FObjectInitializer& ObjectInitializer)
{
	// Create clan component
	ClanComponent = ObjectInitializer.CreateDefaultSubobject<UWHClanManagerComponent>(this, ClanComponentName);
}
