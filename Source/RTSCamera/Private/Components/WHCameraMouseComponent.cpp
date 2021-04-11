// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTSCameraMouseComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
URTSCameraMouseComponent::URTSCameraMouseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	BorderSize = 0.05f;
	OutsideMovement = true;
}


// Called when the game starts
void URTSCameraMouseComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URTSCameraMouseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsInFocus())
		UpdateMouseBorders();
}

FVector2D URTSCameraMouseComponent::GetScreenRelativeMousePosition() const
{
	UObject* WorldContext = GetOwner();
	const FVector2D mouse_pos = UWidgetLayoutLibrary::GetMousePositionOnViewport(WorldContext);
	const FVector2D	view_size = UWidgetLayoutLibrary::GetViewportSize(WorldContext);
	const float scale		  = UWidgetLayoutLibrary::GetViewportScale(WorldContext);
	return (mouse_pos * scale) / view_size;
}

void URTSCameraMouseComponent::UpdateMouseBorders()
{
	const FVector2D pos = GetScreenRelativeMousePosition();
	const uint8 previous = ScreenBorderDirection;

	// Left
	if (pos.X <= BorderSize && (pos.X >= 0 || OutsideMovement))
	{
		// add Flag OR
		ScreenBorderDirection |= static_cast<uint8>(EScreenBorder::Left);
	}
	else
	{
		// remove AND + NOT
		ScreenBorderDirection &= ~static_cast<uint8>(EScreenBorder::Left);
	}

	// Right
	if (1.0 - FMath::Min(1.f,pos.X) <=  BorderSize && (pos.X <= 1 || OutsideMovement))
	{
		ScreenBorderDirection |= static_cast<uint8>(EScreenBorder::Right);
	}
	else
	{
		ScreenBorderDirection &= ~static_cast<uint8>(EScreenBorder::Right);
	}

	// Up
	if (pos.Y <= BorderSize && (pos.Y >= 0 || OutsideMovement))
	{
		ScreenBorderDirection |= static_cast<uint8>(EScreenBorder::Top);
	}
	else
	{
		// remove AND + NOT
		ScreenBorderDirection &= ~static_cast<uint8>(EScreenBorder::Top);
	}

	// Down
	if (1.0 - FMath::Min(1.f, pos.Y) <= BorderSize && (pos.Y <= 1 || OutsideMovement))
	{
		ScreenBorderDirection |= static_cast<uint8>(EScreenBorder::Bottom);
	}
	else
	{
		ScreenBorderDirection &= ~static_cast<uint8>(EScreenBorder::Bottom);
	}

	// Compare and emit updates:;
	if (previous != 0 && ScreenBorderDirection == 0)
		OnLeftBorder.Broadcast();
	if(previous == 0 && ScreenBorderDirection != 0)
		OnEnteredBorder.Broadcast();

	// Update border distances
	const float clampedX = FMath::Clamp(pos.X, 0.f, 1.f);
	const float clampedY = FMath::Clamp(pos.Y, 0.f, 1.f);
	RightBorderScale = (((1 - clampedX)  / BorderSize) * -1) + 1;
	LeftBorderScale = ((clampedX / BorderSize) * -1) + 1;
	TopBorderScale = ((clampedY / BorderSize) * -1) + 1;
	BottomBorderScale = (((1 - clampedY) / BorderSize) * -1) + 1;
}

FVector2D URTSCameraMouseComponent::GetBorderDirection() const
{
	float forward  = (ScreenBorderDirection & static_cast<uint8>(EScreenBorder::Top))	!= 0 ?  1.f : 0;
	float backward = (ScreenBorderDirection & static_cast<uint8>(EScreenBorder::Bottom))!= 0 ? -1.f : 0;
	float right	   = (ScreenBorderDirection & static_cast<uint8>(EScreenBorder::Right)) != 0 ?  1.f : 0;
	float left     = (ScreenBorderDirection & static_cast<uint8>(EScreenBorder::Left))	!= 0 ? -1.f : 0;

	return FVector2D((TopBorderScale * forward) + (backward * BottomBorderScale),(RightBorderScale * right) + (left     * LeftBorderScale));
}

bool URTSCameraMouseComponent::IsInFocus() const
{
	if (auto PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		ULocalPlayer* LocPlayer = PC->GetLocalPlayer();
		if (!LocPlayer->ViewportClient->Viewport || !LocPlayer->ViewportClient->Viewport->IsForegroundWindow())
		{
			return false;
		}
		return true;
	}
	return false;
}
