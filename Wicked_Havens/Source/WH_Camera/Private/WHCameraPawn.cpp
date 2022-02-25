// Copyright © Noé Perard-Gayot 2021.


#include "WHCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AWHCameraPawn::AWHCameraPawn()	: Super()
{
	//Disable Standard WASD Movement
	bAddDefaultMovementBindings = false;

	//Set Default Camera Values
	CameraZoomSpeed = 32.0f;
	CameraDistanceMin = 750.0f;
	CameraDistanceMax = 2000.0f;
	CameraMovementSpeed = 2000.0f;
	CameraScrollBoundary = 25.0f;
	bCanMoveCamera = true;

	//Enable Tick function
	PrimaryActorTick.bCanEverTick = true;

	// create and setup components
	ArmComponent	= CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	ArmComponent->SetupAttachment(GetCollisionComponent());
	ArmComponent->ProbeChannel = ECollisionChannel::ECC_Camera;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(ArmComponent);
}

void AWHCameraPawn::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	//Create variables to hold mouse position and screen size
	FVector2D mousePosition;
	FVector2D viewportSize;

	//Get mouse position and screen size
	UGameViewportClient* gameViewport = GEngine->GameViewport;

	//Make sure viewport exists
	check(gameViewport);
	gameViewport->GetViewportSize(viewportSize);

	//Make sure the viewport has focus(contains the mouse)
	if (gameViewport->IsFocused(gameViewport->Viewport) && gameViewport->GetMousePosition(mousePosition) && bCanMoveCamera)
	{
		//Check if the mouse is at the left or right edge of the screen and move accordingly
		if (mousePosition.X < CameraScrollBoundary)
		{
			MoveCameraRight(-1.0f * deltaSeconds);
		}
		else if (viewportSize.X - mousePosition.X < CameraScrollBoundary)
		{
			MoveCameraRight(1.0f * deltaSeconds);
		}

		//Check if the mouse is at the top or bottom edge of the screen and move accordingly
		if (mousePosition.Y < CameraScrollBoundary)
		{
			MoveCameraForward(1.0f * deltaSeconds);
		}
		else if (viewportSize.Y - mousePosition.Y < CameraScrollBoundary)
		{
			MoveCameraForward(-1.0f * deltaSeconds);
		}
	}
}

void AWHCameraPawn::SetupPlayerInputComponent(class UInputComponent* SetupInputComponent)
{
	Super::SetupPlayerInputComponent(SetupInputComponent);
	check(SetupInputComponent);

	//Bind Mouse Wheel Zooming Actions
	SetupInputComponent->BindAction("WheelMouseUp",		IE_Pressed, this, &AWHCameraPawn::ZoomIn);
	SetupInputComponent->BindAction("WheelMouseDown",	IE_Pressed, this, &AWHCameraPawn::ZoomOut);

	//Bind WASD Movement
	InputComponent->BindAxis("MoveCameraForward",	this, &AWHCameraPawn::MoveCameraForward);
	InputComponent->BindAxis("MoveCameraRight",		this, &AWHCameraPawn::MoveCameraRight);
}

void AWHCameraPawn::ZoomIn()
{
	//Don't execute any further if the camera can't move
	if (!bCanMoveCamera || ArmComponent == nullptr)
		return;

	ArmComponent->TargetArmLength = FMath::Clamp(ArmComponent->TargetArmLength - CameraZoomSpeed, CameraDistanceMin, CameraDistanceMax);
}

void AWHCameraPawn::ZoomOut()
{
	//Don't execute any further if the camera can't move
	if (!bCanMoveCamera)
		return;

	ArmComponent->TargetArmLength = FMath::Clamp(ArmComponent->TargetArmLength + CameraZoomSpeed, CameraDistanceMin, CameraDistanceMax);
}

void AWHCameraPawn::MoveCameraForward(float scale)
{
	//Don't execute any further if the camera can't move
	if (!bCanMoveCamera || CameraComponent == nullptr|| GetMovementComponent() == nullptr)
		return;

	// Get camera rotation
	FRotator CameraRot = CameraComponent->GetComponentToWorld().Rotator();
	CameraRot.Pitch = 0.f;
	CameraRot.Roll = 0.f;

	GetMovementComponent()->AddInputVector((scale * CameraMovementSpeed) * CameraRot.Vector());

}

void AWHCameraPawn::MoveCameraRight(float scale)
{
	//Don't execute any further if the camera can't move
	if (!bCanMoveCamera || CameraComponent == nullptr || GetMovementComponent() == nullptr)
		return;

	// Get camera rotation
	FRotator CameraRot = CameraComponent->GetComponentToWorld().Rotator();
	CameraRot.Pitch = 0.f;
	CameraRot.Roll = 0.f;

	//Add a delta vector that moves by the movementValue in the direction of the camera's yaw
	GetMovementComponent()->AddInputVector((scale * CameraMovementSpeed) * (FRotator(0.0f,90.0f,0.0f) + CameraRot).Vector());
}
