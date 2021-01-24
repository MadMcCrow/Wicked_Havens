// Fill out your copyright notice in the Description page of Project Settings.


#include "WHCameraPawn.h"
#include "Components/WHCameraComponent.h"
#include "Components/WHCameraMovementComponent.h"
#include "Components/WHCameraMouseComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Components static Names
FName AWHCameraPawn::CameraComponentName	 = FName("CameraComponent");
FName AWHCameraPawn::MovementComponentName	 = FName("MovementComponent");
FName AWHCameraPawn::MouseComponentName		 = FName("MouseComponent");
FName AWHCameraPawn::CameraBoomComponentName = FName("CameraBoomComponent");

// Sets default values
AWHCameraPawn::AWHCameraPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Setting parameters default values
	ZoomSpeed = 5.f;
	BaseMovementSpeed = 10.f;
	MaxZoom = 7000.f;
	MinZoom = 300.f;

	// Create Components
	RootComponent		= ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, "RootComponent");
	CameraComponent		= ObjectInitializer.CreateDefaultSubobject<UWHCameraComponent>(this, CameraComponentName);
	CameraBoomComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, CameraBoomComponentName);
	MovementComponent	= ObjectInitializer.CreateDefaultSubobject<UWHCameraMovementComponent>(this, MovementComponentName);
	MouseComponent		= ObjectInitializer.CreateDefaultSubobject<UWHCameraMouseComponent>(this, MouseComponentName);

	// Setup attachement
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraBoomComponent);

	CameraBoomComponent->bDoCollisionTest = false;
	CameraBoomComponent->TargetArmLength = 700;

}

// Called when the game starts or when spawned
void AWHCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (MouseComponent)
	{
		MouseComponent->OnEnteredBorder.AddUniqueDynamic(this, &AWHCameraPawn::StartMouseMovement);
		MouseComponent->OnLeftBorder.AddUniqueDynamic(this, &AWHCameraPawn::EndMouseMovement);
	}
	if (CameraBoomComponent)
	{
		ZoomDistance = CameraBoomComponent->TargetArmLength;
	}
}

// Called every frame
void AWHCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoveBorder && MouseComponent)
	{
		float scale = 0;
		FVector2D border = MouseComponent->GetBorderDirection();
		border.ToDirectionAndLength(border, scale);
		AddMovementInput(FVector(border, 0.f), scale * scale * MovementSpeed()  );
	}

	CameraTracking();

}

// Called to bind functionality to input
void AWHCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(InputAxisForwardName, this, &AWHCameraPawn::MoveAxisForward);
	PlayerInputComponent->BindAxis(InputAxisRightName,   this, &AWHCameraPawn::MoveAxisRight);
	PlayerInputComponent->BindAxis(InputAxisZoomName,	 this, &AWHCameraPawn::Zoom);
}

UPawnMovementComponent* AWHCameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void AWHCameraPawn::SetFreeCamera(bool IsFree)
{
	bIsFreeCamera = IsFree;
}

void AWHCameraPawn::FollowActor(AActor* Target)
{
	if (Target)
	{
		SetFreeCamera(false);
	}
	else
	{
		SetFreeCamera(true);
	}
}

void AWHCameraPawn::MoveAxisForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue * MovementSpeed());
	SetFreeCamera(true);
}

void AWHCameraPawn::MoveAxisRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue );
	SetFreeCamera(true);
}

void AWHCameraPawn::Zoom(float AxisValue)
{
	if (CameraBoomComponent)
	{
		ZoomDistance = FMath::Clamp(ZoomDistance + AxisValue * -1 * (ZoomSpeed * FMath::Sqrt(ZoomDistance)), MinZoom, MaxZoom);
		CameraBoomComponent->TargetArmLength = FMath::FInterpTo(CameraBoomComponent->TargetArmLength, ZoomDistance, GetWorld()->GetDeltaSeconds(), 5.0);
	}
	SetFreeCamera(true);
}

void AWHCameraPawn::CameraTracking()
{
	if (!bIsFreeCamera && TrackedActor)
	{
		FVector direction;
		float length;
		(TrackedActor->GetActorLocation() - GetActorLocation()).ToDirectionAndLength(direction, length);
		AddMovementInput(direction, FMath::Min<float>(length, MovementSpeed()));
	}
}

float AWHCameraPawn::MovementSpeed() const
{
	return FMath::Sqrt(ZoomDistance) * BaseMovementSpeed;
}
