/* Copyright © Noé Perard-Gayot 2022. */


#include "Combat/WHCombatFunctionLibrary.h"

#include "Characters/WHCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

bool UWHCombatFunctionLibrary::FindCombatTarget(AWHCharacter* Character, AActor* OutTarget, bool& OutbInRange,	bool& bIsEnemy)
{
	OutTarget = nullptr;
	if (Character)
	{
		TArray<AActor*> OutActors;
		const float Range = 100; // UE is in cm so that's a meter 
		const FVector Start = Character->GetActorLocation();
		UClass* TargetClass = AActor::StaticClass();
		const auto Type = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
		UKismetSystemLibrary::SphereOverlapActors(Character, Start, Range, {Type}, TargetClass,{Character}, OutActors);
		
	}
	return OutTarget != nullptr;
}

