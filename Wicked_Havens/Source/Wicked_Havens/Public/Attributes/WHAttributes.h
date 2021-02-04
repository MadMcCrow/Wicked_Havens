// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WHAttributes.generated.h"


USTRUCT(BlueprintType)
struct WICKED_HAVENS_API FWHAttribute
{
	GENERATED_BODY()

	/** Value after all computation is done, actual value */
	FVariant Value;

	/** Base value before any modifier, loss of value etc.. */
	FVariant BaseValue;


	FWHAttribute() : Value(), BaseValue()
	{
	}


	FWHAttribute(const FVariant &Base, const FVariant& Value ) : Value(Value), BaseValue(Base)
	{
	}

	bool NetSerialize(FArchive & Ar, class UPackageMap* Map, bool& bOutSuccess);

};

template<>
struct TStructOpsTypeTraits<FWHAttribute> : public TStructOpsTypeTraitsBase2<FWHAttribute>
{
	enum
	{
		WithNetSerializer = true
	};
};


UENUM(BlueprintType)
enum class EWHAttributeTypes : uint8
{
	Health,
	Stamina,
	Speed,
	Sight,
	Attack
};


USTRUCT(BlueprintType)
struct FWHAttributes
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	TMap<EWHAttributeTypes, FWHAttribute > Attributes;

public:

	FWHAttributes() : Attributes(TMap<EWHAttributeTypes, FWHAttribute >())
	{}

	FWHAttributes(const  TMap<EWHAttributeTypes, FWHAttribute >& InMap) : Attributes(InMap)
	{}

	TMap<EWHAttributeTypes, FWHAttribute> GetMap() const {return Attributes; }
};


UINTERFACE(MinimalAPI)
class UAttributesInterface : public UInterface
{
    GENERATED_BODY()
};

class IAttributesInterface
{
    GENERATED_BODY()

public:

    virtual FWHAttributes GetAttributes() const = 0;
    virtual void SetAttributes( const FWHAttributes& NewAttributes) = 0;

};