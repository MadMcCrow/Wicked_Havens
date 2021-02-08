// Fill out your copyright notice in the Description page of Project Settings.


#include "Blackboard/WHBlackboardKeyType_Array.h"


UWHBlackboardKeyType_Array::UWHBlackboardKeyType_Array(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedOp = EBlackboardKeyOperation::Basic;
}

bool UWHBlackboardKeyType_Array::IsAllowedByFilter(UBlackboardKeyType* FilterOb) const
{
	// @todo : make this more complex
	UWHBlackboardKeyType_Array* FilterArray = Cast<UWHBlackboardKeyType_Array>(FilterOb);
	return FilterArray != nullptr;
}
