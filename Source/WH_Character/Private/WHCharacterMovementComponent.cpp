// Copyright © Noé Perard-Gayot 2021.


#include "WHCharacterMovementComponent.h"

void UWHCharacterMovementComponent::PerformMovement(float DeltaSeconds)
{
	if (UpdatedComponent != nullptr)
	{
		const auto OldDirection = UpdatedComponent->GetForwardVector();
		Super::PerformMovement(DeltaSeconds);
		const auto NewDirection = UpdatedComponent->GetForwardVector();
		AngularVelocity = FMath::Acos(OldDirection.Dot(NewDirection));
	}
	else
	{
		Super::PerformMovement(DeltaSeconds);
		AngularVelocity = 0.f;
	}
}

void UWHCharacterMovementComponent::Rotate(const FRotator& Rotation)
{
	FRotator DesiredRotation = Rotation;
	const FRotator CurrentRotation = GetLastUpdateRotation();
	const FRotator DeltaRot = GetDeltaRotation(GetWorld()->GetDeltaSeconds());
	if (ShouldRemainVertical())
	{
		DesiredRotation.Pitch = 0.f;
		DesiredRotation.Yaw = FRotator::NormalizeAxis(DesiredRotation.Yaw);
		DesiredRotation.Roll = 0.f;
	}
	else
	{
		DesiredRotation.Normalize();
	}

	// Accumulate a desired new rotation.
	constexpr float AngleTolerance = 1e-3f;
	if (!CurrentRotation.Equals(DesiredRotation, AngleTolerance))
	{
		// PITCH
		if (!FMath::IsNearlyEqual(CurrentRotation.Pitch, DesiredRotation.Pitch, AngleTolerance))
		{
			DesiredRotation.Pitch = FMath::FixedTurn(CurrentRotation.Pitch, DesiredRotation.Pitch, DeltaRot.Pitch);
		}
		// YAW
		if (!FMath::IsNearlyEqual(CurrentRotation.Yaw, DesiredRotation.Yaw, AngleTolerance))
		{
			DesiredRotation.Yaw = FMath::FixedTurn(CurrentRotation.Yaw, DesiredRotation.Yaw, DeltaRot.Yaw);
		}
		// ROLL
		if (!FMath::IsNearlyEqual(CurrentRotation.Roll, DesiredRotation.Roll, AngleTolerance))
		{
			DesiredRotation.Roll = FMath::FixedTurn(CurrentRotation.Roll, DesiredRotation.Roll, DeltaRot.Roll);
		}
	}
	// Set the new rotation.
	MoveUpdatedComponent( FVector::ZeroVector, DesiredRotation, /*bSweep*/ false );
}
