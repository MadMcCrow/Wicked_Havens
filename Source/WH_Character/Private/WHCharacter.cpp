/* Copyright © Noé Perard-Gayot 2021. */

#include "WHCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


AWHCharacter::AWHCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWHCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AWHCharacter::MoveRight(float Value)
{
	if (const auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		Movement->AddInputVector(GetActorRightVector() * Value);
	}
}

void AWHCharacter::MoveForward(float Value)
{
	if (const auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		Movement->AddInputVector(GetActorForwardVector() * Value);
	}
}

void AWHCharacter::LookAt(const FVector &Target)
{
	if (const auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		Rotate(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target));
	}
}

void AWHCharacter::Rotate(const FRotator& Rotation) const
{
	if (const auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		FRotator DesiredRotation = Rotation;
		const FRotator CurrentRotation = Movement->GetLastUpdateRotation();
		const FRotator DeltaRot = Movement->GetDeltaRotation(GetWorld()->GetDeltaSeconds());

		if (Movement->ShouldRemainVertical())
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
		Movement->MoveUpdatedComponent( FVector::ZeroVector, DesiredRotation, /*bSweep*/ false );
	}
}
