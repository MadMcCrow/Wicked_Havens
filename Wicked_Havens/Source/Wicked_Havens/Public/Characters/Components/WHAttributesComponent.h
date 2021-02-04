// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/WHAttributes.h"
#include "Components/ActorComponent.h"
#include "WHAttributesComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WICKED_HAVENS_API UWHAttributesComponent : public UActorComponent, public IAttributesInterface
{
	GENERATED_BODY()


	virtual FWHAttributes GetAttributes() const override;
	virtual void SetAttributes(const FWHAttributes& NewAttributes) override;

	virtual void OnRegister() override;

protected:

	/** Predefined Attributes for this Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSoftObjectPtr<class UWHAttributesAsset> DefaultAttributes;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FWHAttributes CharacterAttributes;



};
