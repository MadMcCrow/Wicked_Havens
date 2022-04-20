/* Copyright © Noé Perard-Gayot 2022. */

#include "Characters/WHCharacter.h"

#include "WHAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/WHPlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/WHInventoryComponent.h"

AWHCharacter::AWHCharacter() : Super()
{
	AttributeComponent = CreateDefaultSubobject<UWHAttributeComponent>(TEXT("Attributes"));
	InventoryComponent = CreateDefaultSubobject<UWHInventoryComponent>(TEXT("Inventory"));

	CameraComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("CameraActor"));
	CameraComponent->SetChildActorClass(AWHPlayerCamera::StaticClass());
}
