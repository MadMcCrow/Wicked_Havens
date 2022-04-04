/* Copyright © Noé Perard-Gayot 2022. */

#pragma once

#include "WHCharacterBase.h"
#include "Combat/WHTargetableInterface.h"
#include "WHCharacter.generated.h"



/**
 *	@class AWHCharacter
 *	Base class for characters in Wicked havens. collection of components
 *	@todo :
 *			- move camera handling out of this class
 */
UCLASS(BlueprintType, Category = "Wicked Havens")
class WICKED_HAVENS_API AWHCharacter : public AWHCharacterBase, public IWHTargetableInterface
{
	GENERATED_BODY()

public:

	AWHCharacter();
	
private:

	/** Attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Wicked Havens|Attributes", meta=(AllowPrivateAccess))
	class UWHAttributeComponent* AttributeComponent;

	/** Inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Wicked Havens|Inventory", meta=(AllowPrivateAccess))
	class UWHInventoryComponent* InventoryComponent;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wicked Havens|Camera", meta = (AllowPrivateAccess))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wicked Havens|Camera", meta = (AllowPrivateAccess))
	class USpringArmComponent* CameraArmComponent;

	
public:

	FORCEINLINE UWHAttributeComponent* GetAttributeComponent() const {return AttributeComponent;}
	FORCEINLINE UWHInventoryComponent* GetInventoryComponent() const {return InventoryComponent;}
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return CameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraArmComponent() const { return CameraArmComponent; }
};
