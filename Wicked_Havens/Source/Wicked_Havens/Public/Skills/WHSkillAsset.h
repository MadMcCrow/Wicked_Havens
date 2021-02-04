// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WHSkill.h"
#include "Engine/DataAsset.h"
#include "WHSkillAsset.generated.h"

//forward declaration
class UWHSkillEffect;

UCLASS()
class WICKED_HAVENS_API UWHSkillAsset : public UDataAsset
{
	GENERATED_BODY()


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FWHSkill SkillInfo;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	TSoftClassPtr<UWHSkillEffect> Effect;


};
