// Fill out your copyright notice in the Description page of Project Settings.


#include "Blackboard/WHBlackboardKeyType_ArrayOfObject.h"
#include "UObject/WeakObjectPtr.h"

UWHBlackboardKeyType_ArrayOfObject::UWHBlackboardKeyType_ArrayOfObject() : Super()
{
	ValueSize = sizeof(TArray<FWeakObjectPtr>) + sizeof(uint32);
}

bool UWHBlackboardKeyType_ArrayOfObject::IsAllowedByFilter(UBlackboardKeyType* FilterOb) const 
{
	UWHBlackboardKeyType_ArrayOfObject* FilterArray = Cast<UWHBlackboardKeyType_ArrayOfObject>(FilterOb);
	return FilterArray != nullptr;
}

FString UWHBlackboardKeyType_ArrayOfObject::DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const
{
	TArray<FWeakObjectPtr> Array = GetValue(this, RawData);
	return Array.Num() <=0 ? DescribeSelf() + FString(" - Empty") : DescribeSelf() + FString(" - of Size ") + FString::FromInt(Array.Num());
}

FString UWHBlackboardKeyType_ArrayOfObject::DescribeSelf() const
{
	return FString("Array Of Objects");
}
