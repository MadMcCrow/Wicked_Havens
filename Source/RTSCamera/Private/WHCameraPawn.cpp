// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"
#include "Components/RTSCameraComponent.h"
#include "Components/RTSCameraMovementComponent.h"
#include "Components/RTSCameraMouseComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Components static Names
FName ARTSCameraPawn::CameraComponentName	 = FName("CameraComponent");
FName ARTSCameraPawn::MovementComponentName	 = FName("MovementComponent");
FName ARTSCameraPawn::MouseComponentName		 = FName("MouseComponent");
FName ARTSCameraPawn::CameraBoomComponentName = FName("CameraBoomComponent");

// Sets default values
ARTSCameraPawn::ARTSCameraPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<URTSCameraMovementComponent>(ASpectatorPawn::MovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	// Setting parameters default values
	ZoomSpeed = 5.f;
	BaseMovementSpeed = 10.f;
	MaxZoom = 7000.f;
	MinZoom = 300.f;

	// Create Components
	RootComponent		= ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, "RootComponent");
	CameraComponent		= ObjectInitializer.CreateDefaultSubobject<URTSCameraComponent>(this, CameraComponentName);
	CameraBoomComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, CameraBoomComponentName);
	MouseComponent		= ObjectInitializer.CreateDefaultSubobject<URTSCameraMouseComponent>(this, MouseComponentName);

	// Setup attachement
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(CameraBoomComponent);

	CameraBoomComponent->bDoCollisionTest = false;
	CameraBoomComponent->TargetArmLength = 700;

}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (MouseComponent)
	{
		MouseComponent->OnEnteredBorder.AddUniqueDynamic(this, &ARTSCameraPawn::StartMouseMovement);
		MouseComponent->OnLeftBorder.AddUniqueDynamic(this, &ARTSCameraPawn::EndMouseMovement);
	}
	if (CameraBoomComponent)
	{
		ZoomDistance = CameraBoomComponent->TargetArmLength;
	}
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
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
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(InputAxisForwardName, this, &ARTSCameraPawn::MoveAxisForward);
	PlayerInputComponent->BindAxis(InputAxisRightName,   this, &ARTSCameraPawn::MoveAxisRight);
	PlayerInputComponent->BindAxis(InputAxisZoomName,	 this, &ARTSCameraPawn::Zoom);
}

UPawnMovementComponent* ARTSCameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void ARTSCameraPawn::SetFreeCamera(bool IsFree)
{
	bIsFreeCamera = IsFree;
}

void ARTSCameraPawn::FollowActor(AActor* Target)
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

void ARTSCameraPawn::MoveAxisForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue * MovementSpeed());
	SetFreeCamera(true);
}

void ARTSCameraPawn::MoveAxisRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue );
	SetFreeCamera(true);
}

void ARTSCameraPawn::Zoom(float AxisValue)
{
	if (CameraBoomComponent)
	{
		ZoomDistance = FMath::Clamp(ZoomDistance + AxisValue * -1 * (ZoomSpeed * FMath::Sqrt(ZoomDistance)), MinZoom, MaxZoom);
		CameraBoomComponent->TargetArmLength = FMath::FInterpTo(CameraBoomComponent->TargetArmLength, ZoomDistance, GetWorld()->GetDeltaSeconds(), 5.0);
	}
	SetFreeCamera(true);
}

void ARTSCameraPawn::CameraTracking()
{
	if (!bIsFreeCamera && TrackedActor)
	{
		FVector direction;
		float length;
		(TrackedActor->GetActorLocation() - GetActorLocation()).ToDirectionAndLength(direction, length);
		AddMovementInput(direction, FMath::Min<float>(length, MovementSpeed()));
	}
}

float ARTSCameraPawn::MovementSpeed() const
{
	return FMath::Sqrt(ZoomDistance) * BaseMovementSpeed;
}
