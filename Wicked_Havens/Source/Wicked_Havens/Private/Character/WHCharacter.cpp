// Copyright © Noé Perard-Gayot 2021.


#include "Character/WHCharacter.h"
#include "Character/WHCharacterData.h"

// Sets default values
AWHCharacter::AWHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWHCharacter::BeginPlay()
{
	Super::BeginPlay();

	// apply the Character's data
	ApplyCharacterData();
}


void AWHCharacter::ApplyCharacterData() const
{
	// call the BP variant
	LoadCharacterData();

	if (auto Char = CharData.Get())
	{
		if (auto Skl = GetMesh())
			Skl->SetSkeletalMeshWithoutResettingAnimation(CharData->GetMesh());
	}
	ApplyCharacterData_BP(CharData.Get());
}

void AWHCharacter::SetCharacterData(const TSoftObjectPtr<UWHCharacterData> &NewCharData)
{
	// do not do anything if new char data is not valid
	if (!NewCharData.IsNull())
	{
		CharData = NewCharData;

		// if we already began play, update
		if (HasActorBegunPlay())
		{
			ApplyCharacterData();
		}
	}
}

void AWHCharacter::LoadCharacterData() const
{
	if (!CharData.IsNull())
	{
		if (HasActorBegunPlay())
		{
			CharData.LoadSynchronous();
		}
	}
	
}