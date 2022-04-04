/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "Components/SceneComponent.h"
#include "WHTargetingComponent.generated.h"


/**
 *	@class UWHTargetingComponent
 *	a component to figure out who you're fighting
 */
UCLASS(ClassGroup=(WH), Category="Wicked Havens|Combat", Meta = (DisplayName="Combat Targeting Component"))
class WICKED_HAVENS_API UWHTargetingComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:

	// CTR :
	UWHTargetingComponent();

	// <USceneComponent-API>
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// <\USceneComponent-API>
	
	/**
	 *	 @func FindAvailableTargetActors
	 *	 Look for targets in a cone in front of us
	 */
	UFUNCTION(BlueprintCallable, Category="Combat|Targeting")
	bool FindAvailableTargetActors(TArray<AActor*>& OutTargets) const;

	/**
	 *	 @func FindAvailableTargetComponents
	 *	 Look for targets in a cone in front of us
	 */
	UFUNCTION(BlueprintCallable, Category="Combat|Targeting")
	bool FindAvailableTargetComponents(TArray<UActorComponent*>& OutTargets) const;

	/**
	 *	 @func SetRange
	 *	 @param InRange	New range for this component
	 *	 Updates the range for finding targets.
	 *	 @note:
	 *			- Defines the range finding capability, not the effective attack range
	 */
	UFUNCTION(BlueprintSetter, BlueprintCallable, Category="Combat|Targeting")
	void SetRange(float InRange);
	
protected:

	/** The range of the cone, in cm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter="SetRange", Category="Combat|Targeting")
	float Range;
	
	/** The angle of the cone, in radian */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Targeting")
	float Angle;

	/**
	 *	@func GetConeTest
	 *	return either the cached Cone collisions, or the result of @see PerformConeTest
	 */
	const TArray<FOverlapResult>& GetConeTraceResults() const;


private:
	/**
	 *	@func PerformConeTest
	 *	Does the actual cone check
	 *	It cannot be made async because async would mean getting the result the next frame, meaning less responsiveness
	 *	but we make sure it's done at most once per frame.
	 */
	bool PerformConeTest() const;

	/** Cached Collisions calculated from PerformConeTest */
	UPROPERTY(Transient)
	mutable TArray<FOverlapResult> CachedConeCollisions;

	/** wether we performed ConeCollision this frame */
	UPROPERTY(Transient)
	mutable bool bConeCollisionCached;
	
protected:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Targeting|Debug")
	bool bShowDebug;
#endif // WITH_EDITORONLY_DATA

#if WITH_EDITOR
	void DrawDebug() const;
#endif // WITH_EDITOR
};
