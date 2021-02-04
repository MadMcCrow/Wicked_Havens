// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "WHBlackboardKeyType_Array.generated.h"



/**
 * 
 */
UCLASS(Abstract)
class WH_AI_API UWHBlackboardKeyType_Array : public UBlackboardKeyType
{
	GENERATED_BODY()

public:

	UWHBlackboardKeyType_Array(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	template<typename T>
	static TArray<T> GetArray(const UWHBlackboardKeyType_Array* KeyOb, const uint8* RawData)
	{
	if (RawData == nullptr) {return TArray<T>();}
	return GetValueFromMemory<TArray<T>>(RawData);
	}

	template<typename T>
	static bool SetArray(UWHBlackboardKeyType_Array* KeyOb, uint8* RawData, const TArray<T> &Value)
	{
		return SetValueInMemory<TArray<T>>(RawData, Value);
	}

	template<typename T>
	bool ArrayIsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const
	{
		return GetValueFromMemory<TArray<T>>(MemoryBlock).Num() <= 0;
	}

	template<typename T>
	EBlackboardCompare::Type CompareArrays(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,	const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
	{
		if (auto OtherArrayKey = Cast<UWHBlackboardKeyType_Array>(OtherKeyOb))
		{
			return GetArray<T>(this,MemoryBlock) == GetArray<T>(OtherArrayKey,OtherMemoryBlock) ? EBlackboardCompare::Equal : EBlackboardCompare::NotEqual;
		}
		return EBlackboardCompare::NotEqual;
	}

	virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;

protected:

	template<typename T>
	bool TestBasicOperationArray(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const
	{
		return (Op == EBasicKeyOperation::NotSet) == ArrayIsEmpty<T>(OwnerComp,MemoryBlock); // either false,false -> Set/NotEmpty, or true,true ->NotSet/Empty
	}



	
};
