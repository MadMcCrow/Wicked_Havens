/* Copyright © Noé Perard-Gayot 2022. */

#include "Characters/WHCharacter.h"

#include "WHAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/WHInventoryComponent.h"

AWHCharacter::AWHCharacter() : Super()
{
	AttributeComponent = CreateDefaultSubobject<UWHAttributeComponent>(TEXT("Attributes"));
	InventoryComponent = CreateDefaultSubobject<UWHInventoryComponent>(TEXT("Inventory"));

	// Create a camera boom...
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArmComponent->SetupAttachment(RootComponent);
	CameraArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraArmComponent->TargetArmLength = 800.f;
	CameraArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}
