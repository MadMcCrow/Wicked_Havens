/* Copyright © Noé Perard-Gayot 2022. */

#include "Camera/WHPlayerCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWHPlayerCamera::AWHPlayerCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create a camera boom...
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArmComponent->SetupAttachment(RootComponent);
	CameraArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraArmComponent->TargetArmLength = 800.f;
	CameraArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
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
}
