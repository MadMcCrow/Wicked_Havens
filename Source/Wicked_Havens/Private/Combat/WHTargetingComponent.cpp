/* Copyright © Noé Perard-Gayot 2022. */


#include "Combat/WHTargetingComponent.h"

#include "Combat/WHTargetableInterface.h"

UWHTargetingComponent::UWHTargetingComponent()
: Super()
, Range(200)
, bConeCollisionCached(false)
{
	
}

void UWHTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType,	FActorComponentTickFunction* ThisTickFunction)
{
	// begining of frame : "clear cache"
	bConeCollisionCached = false;
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
#if WITH_EDITOR && WITH_EDITORONLY_DATA
	DrawDebug();
#endif // WITH_EDITOR && WITH_EDITORONLY_DATA
	
}

bool UWHTargetingComponent::FindAvailableTargetActors(TArray<AActor*>& OutTargets) const
{
	const auto& Collisions = GetConeTraceResults();
	OutTargets.Empty(Collisions.Num());
	for (const auto& Collision : Collisions)
	{
		if (auto Actor = Collision.GetActor())
		{
			if (Actor->Implements<UWHTargetableInterface>())
			{
				OutTargets.AddUnique(Actor);
			}
		}
	}
	OutTargets.Shrink();
	return OutTargets.Num() > 0;
}

bool UWHTargetingComponent::FindAvailableTargetComponents(TArray<UActorComponent*>& OutTargets) const
{
	const auto& Collisions = GetConeTraceResults();
	OutTargets.Empty(Collisions.Num());
	for (const auto& Collision : Collisions)
	{
		if (auto Component = Collision.GetComponent())
		{
			if (Component->Implements<UWHTargetableInterface>())
			{
				OutTargets.AddUnique(Component);
			}
		}
	}
	OutTargets.Shrink();
	return OutTargets.Num() > 0;
}

void UWHTargetingComponent::SetRange(float InRange)
{
	Range = InRange;
	// perform checks or whatever
}

const TArray<FOverlapResult>& UWHTargetingComponent::GetConeTraceResults() const
{
	if (bConeCollisionCached)
	{
		return CachedConeCollisions;
	}
	if (PerformConeTest())
	{
		bConeCollisionCached = true;
	}
	return CachedConeCollisions;
}

bool UWHTargetingComponent::PerformConeTest() const
{
	const auto World = GetWorld();

	if (!World)
		return false;
	
	// Get the necessary info about us
	const auto Transform = GetComponentTransform();
	const auto Forward = Transform.TransformVector(FVector::ForwardVector);
	const auto CosAngle = FMath::Cos(Angle);

	// perform collision check
	FCollisionObjectQueryParams ObjectQueryParams(FCollisionObjectQueryParams::AllDynamicObjects);
	FCollisionQueryParams CollisionQueryParams ;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	// do the overlap test;
	World->OverlapMultiByObjectType( CachedConeCollisions,Transform.GetLocation(),Transform.GetRotation(),ObjectQueryParams, FCollisionShape::MakeSphere(Range),CollisionQueryParams);

	
	// remove out of angle : cos(θ) = (a · b) .
	// with :
	//	a = targeting comp forward vector, normalized
	//  b = relative position of collision, normalized
	CachedConeCollisions.RemoveAll([&Transform, &Forward, &CosAngle](const FOverlapResult& CollisionItr)
	{
		const auto CollPosRel = Transform.InverseTransformPosition(CollisionItr.GetComponent()->GetComponentLocation()).GetUnsafeNormal();
		return (Forward.Dot(CollPosRel)) <= CosAngle;
	});
	return CachedConeCollisions.Num() >= 0;
}

#if WITH_EDITOR
void UWHTargetingComponent::DrawDebug() const
{
#if WITH_EDITORONLY_DATA
	if (bShowDebug)
	{
		const auto Transform = GetComponentTransform();
		const auto Location	= Transform.GetLocation();
		const auto Forward		= Transform.TransformVector(FVector::ForwardVector);
		DrawDebugCone(GetWorld(), Location, Forward, Range, Angle, Angle, 16, FColor::Cyan, false, -1, 0 ,.01);

		TArray<AActor*> TargetableActors;
		FindAvailableTargetActors(TargetableActors);
		for (const auto& Actor : TargetableActors)
		{
			FVector Loc, Ext;
			Actor->GetActorBounds(true, Loc, Ext, false);
			DrawDebugBox(GetWorld(), Loc,Ext, FColor::Magenta, false, -1, 0 ,.01);
		}
	}
#endif // WITH_EDITORONLY_DATA
}
#endif // WITH_EDITOR
