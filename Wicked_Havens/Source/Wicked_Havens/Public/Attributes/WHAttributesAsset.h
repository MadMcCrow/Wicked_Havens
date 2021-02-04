// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WHAttributes.h"
#include "WHAttributesAsset.generated.h"

UCLASS()
class WICKED_HAVENS_API UWHAttributesAsset : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FWHAttributes Attributes;

public:

	FORCEINLINE UFUNCTION(BlueprintPure, Category = "Attributes")
	const FWHAttributes &GetAttributes() const { return Attributes; }
};

