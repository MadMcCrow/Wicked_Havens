/* Copyright © Noé Perard-Gayot 2022. */

#include "Debug/WHDebugSubsystem.h"
#include "Widgets/SBoxPanel.h"
#include "Engine/GameViewportClient.h"

void UWHDebugSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UWHDebugSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UWHDebugSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!DebugContainer.IsValid())
	{
		InitDebugWidgets();
	}
}

void UWHDebugSubsystem::InitDebugWidgets()
{
	/*
	const auto Player = GetLocalPlayer();
	const auto Client = Player ? Player->ViewportClient : nullptr;
	const auto Viewport = Client ? Client->GetGameViewportWidget() : nullptr;
	if (!Client)
		return;
	DebugContainer = SNew(SVerticalBox);
	Client->AddViewportWidgetContent(DebugContainer.ToSharedRef(), 0);
	*/
}

