// Copyright © Noé Perard-Gayot 2021.


#include "WHAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UWHAnimInstance::UWHAnimInstance() : Super(), SpeedThreshold(KINDA_SMALL_NUMBER)
{
}

void UWHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = GetCharacter();
}

FVector UWHAnimInstance::GetMovementVelocity() const
{
	if(const auto Mov = GetMovementComponent())
	{
		return Mov->Velocity;
	}
	return FVector::ZeroVector;
}

float UWHAnimInstance::GetMovementSpeed() const
{
	return GetMovementVelocity().Size();
}

float UWHAnimInstance::GetMovementAngle() const
{
	if (const USkeletalMeshComponent* OwnerComponent = GetSkelMeshComponent())
	{
		return FVector::DotProduct(GetMovementVelocity().GetSafeNormal(), OwnerComponent->GetForwardVector());
	}
	return 0.f;
}

bool UWHAnimInstance::IsMoving() const
{
	return GetMovementSpeed() > SpeedThreshold;
}

bool UWHAnimInstance::IsInAir() const
{
	if(const auto Mov = GetMovementComponent())
	{
		return Mov->IsFalling();
	}
	return false;
}

ACharacter* UWHAnimInstance::GetCharacter() const
{
	if (OwningCharacter)
	{
		return OwningCharacter;
	}
	else
	{
		// may not be thread safe thought !!!
		UWHAnimInstance* const mutable_this = const_cast<UWHAnimInstance*>(this);
		mutable_this->OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
		return mutable_this->OwningCharacter;
	}
}

UCharacterMovementComponent* UWHAnimInstance::GetMovementComponent() const
{
	if (const auto Character = GetCharacter())
	{
		return Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	}
	return nullptr;
}
