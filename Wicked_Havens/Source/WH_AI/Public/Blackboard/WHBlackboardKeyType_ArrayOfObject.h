// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WHBlackboardKeyType_Array.h"
#include "WHBlackboardKeyType_ArrayOfObject.generated.h"



/**
 * 
 */
UCLASS(EditInlineNew, meta=(DisplayName="Array Of Object"))
class WH_AI_API UWHBlackboardKeyType_ArrayOfObject : public UWHBlackboardKeyType_Array
{
	GENERATED_BODY()

public:
	static TArray<FWeakObjectPtr> GetValue(const UWHBlackboardKeyType_Array* KeyOb, const uint8* RawData) {return GetArray<FWeakObjectPtr>(KeyOb, RawData);}
	static bool SetValue(UWHBlackboardKeyType_Array* KeyOb, uint8* RawData, const TArray<FWeakObjectPtr> &Value){return SetArray(KeyOb, RawData, Value);}
	EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,	const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override
	{
		return CompareArrays<FWeakObjectPtr>(OwnerComp,MemoryBlock,	OtherKeyOb, OtherMemoryBlock);
	}
	virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const	 override {return GetValue(this,MemoryBlock).Num() <= 0;	}

protected:
	virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const	{return TestBasicOperationArray<FWeakObjectPtr>(OwnerComp,MemoryBlock, Op);}


public:
	virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;
	virtual FString DescribeSelf() const override;
protected:
	virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;
	
};
