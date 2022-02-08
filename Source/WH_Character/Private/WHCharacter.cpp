/* Copyright © Noé Perard-Gayot 2021. */

#include "WHCharacter.h"

#include "WHCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// enhanced input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AWHCharacter::AWHCharacter(const FObjectInitializer& ObjectInitializer)
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

void AWHCharacter::PawnClientRestart()
{
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

void AWHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto  PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (DefaultMoveAction)
		{
			PlayerEnhancedInputComponent->BindAction(DefaultMoveAction, ETriggerEvent::Triggered, this, &AWHCharacter::OnMoveAction);
		}
	}
}

void AWHCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AWHCharacter::LookAt(const FVector &Target)
{
	if (const auto Movement = GetCharacterMovementComponent())
	{
		Movement->Rotate(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target));
	}
}

void AWHCharacter::OnMoveAction(const FInputActionInstance& ActionInstance)
{
	switch(ActionInstance.GetValue().GetValueType())
	{
	case EInputActionValueType::Boolean:
		AddMovementInput(FVector::ForwardVector);
		break;
	case EInputActionValueType::Axis1D:
		AddMovementInput(FVector(ActionInstance.GetValue().Get<float>(), 0.f, 0.f));
		break;
	case EInputActionValueType::Axis2D:
		AddMovementInput(FVector(ActionInstance.GetValue().Get<FVector2D>(), 0.f));
		break;
	case EInputActionValueType::Axis3D:
		AddMovementInput(ActionInstance.GetValue().Get<FVector>());
		break;
	}
}

UWHCharacterMovementComponent* AWHCharacter::GetCharacterMovementComponent() const
{
	return Cast<UWHCharacterMovementComponent>(GetMovementComponent());
}

bool AWHCharacter::GetOrientToMovement() const
{
	if (const auto Movement = GetCharacterMovementComponent())
	{
		return Movement->bOrientRotationToMovement;
	}
	return false;
}
