/* Copyright © Noé Perard-Gayot 2022. */

#include "WHCharacterBase.h"

#include "Animation/WHCharacterMovementComponent.h"
#include "Action/WHCharacterAction.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


AWHCharacterBase::AWHCharacterBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UWHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWHCharacterBase::PawnClientRestart()
{
	// Idea : move to clear up the component
	Super::PawnClientRestart();
	if (auto PC = Cast<APlayerController>(GetController()))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();
			// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AWHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind all actions
	if (const auto  PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for (const auto& Action  : CharacterActions)
		{
			if (Action)
				Action->BindInputAction(PlayerEnhancedInputComponent);
		}
	}
}

void AWHCharacterBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AWHCharacterBase::LookAt(const FVector &Target)
{
	if (const auto Movement = GetCharacterMovementComponent())
	{
		Movement->Rotate(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target));
	}
}

UWHCharacterMovementComponent* AWHCharacterBase::GetCharacterMovementComponent() const
{
	return Cast<UWHCharacterMovementComponent>(GetMovementComponent());
}

bool AWHCharacterBase::GetOrientToMovement() const
{
	if (const auto Movement = GetCharacterMovementComponent())
	{
		return Movement->bOrientRotationToMovement;
	}
	return false;
}
