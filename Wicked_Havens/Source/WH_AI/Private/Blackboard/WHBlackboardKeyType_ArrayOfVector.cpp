// Fill out your copyright notice in the Description page of Project Settings.


#include "Blackboard/WHBlackboardKeyType_ArrayOfVector.h"
#include "UObject/WeakObjectPtr.h"

bool UWHBlackboardKeyType_ArrayOfVector::IsAllowedByFilter(UBlackboardKeyType* FilterOb) const 
{
	UWHBlackboardKeyType_ArrayOfVector* FilterArray = Cast<UWHBlackboardKeyType_ArrayOfVector>(FilterOb);
	return FilterArray != nullptr;
}

FString UWHBlackboardKeyType_ArrayOfVector::DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const
{
	TArray<FVector> Array = GetValue(this, RawData);
	return Array.Num() <=0 ? DescribeSelf() + FString(" - Empty") : DescribeSelf() + FString(" - of Size ") + FString::FromInt(Array.Num());
}

FString UWHBlackboardKeyType_ArrayOfVector::DescribeSelf() const
{
	return FString("Array Of Vector");
}
