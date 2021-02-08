// Fill out your copyright notice in the Description page of Project Settings.

#include "WH_SaveGame.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, WH_SaveGame, "WH_SaveGame" );

DEFINE_LOG_CATEGORY(LogWHSaveGame);


void FWH_SaveGame::StartupModule()
{
	IModuleInterface::StartupModule();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogWHSaveGame, Display, TEXT("WH_SaveGame module started"));
#endif // !UE_BUILD_SHIPPING
}

void FWH_SaveGame::ShutdownModule()
{
	IModuleInterface::StartupModule();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogWHSaveGame, Display, TEXT("WH_SaveGame module shutdown"));
#endif // !UE_BUILD_SHIPPING
}