// Copyright © Noé Perard-Gayot 2021.


#include "WHAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	return FVector();
}

float UWHAnimInstance::GetMovementSpeed() const
{
	return GetMovementVelocity().Size();
}

bool UWHAnimInstance::GetIsInAir() const
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
