// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSCameraMouseComponent.generated.h"

/**
 *	Enum to describe screen borders
 */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EScreenBorder : uint8
{
	None	= 0 UMETA(Hidden),
	Top		= 1 << 0	UMETA(DisplayName="Top"),
	Bottom	= 1 << 1	UMETA(DisplayName = "Bottom"),
	Left	= 1 << 2	UMETA(DisplayName = "Left"),
	Right   = 1 << 3	UMETA(DisplayName = "Right")
};
ENUM_CLASS_FLAGS(EScreenBorder);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBorderEvent);

/**
 *	component to handle mouse movement for the camera
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "Mouse")
class WH_CAMERA_API URTSCameraMouseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URTSCameraMouseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	// Delegate for event when mouse cursor enters screen border
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Event")
	FBorderEvent OnEnteredBorder;

	// Delegate for event when mouse cursor leaves screen border
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Event")
	FBorderEvent OnLeftBorder;

	// Size of the border in screen percentage {0,.5}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse", meta = (UIMin = "0.0", UIMax = "0.5"))
	float BorderSize;

	// whether we should consider movement outside of the viewport
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	bool OutsideMovement;

	UFUNCTION(BlueprintPure, Category = "Mouse")
	FVector2D GetScreenRelativeMousePosition() const;

	/** Simple Blueprint getter for ScreenBorderDirection updated by @see UpdateMouseBorders */
	UFUNCTION(BlueprintPure, Category = "Mouse")
	UPARAM(DisplayName="Border", meta=(Bitmask, BitmaskEnum = EScreenBorder))uint8 GetScreenBorderDirection() const { return ScreenBorderDirection; }

	/** Simple Blueprint getter for ScreenBorderDirection updated by @see UpdateMouseBorders */
	UFUNCTION(BlueprintPure, Category = "Mouse")
	UPARAM(DisplayName = Border) float GetScreenBorderDistance(EScreenBorder border) const { return 0.f; }

private:

	/** In What direction the mouse is currently in the border */
	UPROPERTY(Transient)
	uint8 ScreenBorderDirection = 0;


	/**
	 *	how close to the top border are we
	 *  {1,0} 1 is at the border 0 is far away
	 */
	UPROPERTY(Transient)
	float TopBorderScale  = 0;

	/**
	 *	how close to the bottom border are we
	 *  {1,0} 1 is at the border 0 is far away
	 */
	UPROPERTY(Transient)
	float BottomBorderScale = 0;

	/**
	 *	how close to the right border are we
	 *  {1,0} 1 is at the border 0 is far away
	 */
	UPROPERTY(Transient)
	float RightBorderScale = 0;

	/**
	 *	how close to the left border are we
	 *  {1,0} 1 is at the border 0 is far away
	 */
	UPROPERTY(Transient)
	float LeftBorderScale = 0;



	UFUNCTION()
	void UpdateMouseBorders();

public:

	UFUNCTION(BlueprintPure, Category = "Mouse")
	virtual FVector2D GetBorderDirection() const;

	UFUNCTION(BlueprintPure, Category ="Mouse")
	bool IsInFocus() const;

};
