/* Copyright © Noé Perard-Gayot 2022. */

#include "Camera/WHPlayerCamera.h"

#include "WHCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/WHPlayerController.h"

AWHPlayerCamera::AWHPlayerCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create a camera boom...
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	GetArmComponent()->SetupAttachment(RootComponent);
	GetArmComponent()->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	GetArmComponent()->TargetArmLength = 800.f;
	GetArmComponent()->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	GetArmComponent()->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	GetCameraComponent()->SetupAttachment(CameraArmComponent, USpringArmComponent::SocketName);
	GetCameraComponent()->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	
}

void AWHPlayerCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AWHPlayerCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bFreeCamera)
	{
		// todo : add this to set free function
		GetMovementComponent()->Deactivate();
		// todo : do lerp, smooth movement
		if (auto Controller = Cast<AWHPlayerController>(GetController()))
		{
			if (const auto ControlledChar = Controller->GetActiveActionCharacter())
			{
				SetActorLocation(ControlledChar->GetActorLocation());
			}
		}
	}
}
