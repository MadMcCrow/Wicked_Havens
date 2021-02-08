// Fill out your copyright notice in the Description page of Project Settings.

#include "WHAILibrary.h"

EAIAction UWHAILibrary::GetActionForTarget(FVector Target)
{
	return EAIAction::None;
}

bool UWHAILibrary::SetTargetForPlayerAI(FVector Target)
{
	return false;
}

AWHAIController* UWHAILibrary::GetUserControlledAIController()
{
	return nullptr;
}