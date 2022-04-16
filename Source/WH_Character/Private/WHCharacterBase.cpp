/* Copyright © Noé Perard-Gayot 2022. */

#include "WHCharacterBase.h"

#include "Animation/WHCharacterMovementComponent.h"
#include "Action/WHCharacterAction.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/WHActionFunctionLibrary.h"


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

void AWHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (const auto PlayerController = Cast<APlayerController>(GetController()))
	{
		// this function may be called multiple times, so we remove first, before adding
		for (const auto Action : CharacterActions)
		{
			UWHActionFunctionLibrary::RemoveAction(PlayerController, Action);
			UWHActionFunctionLibrary::AddAction(PlayerController, Action);
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
