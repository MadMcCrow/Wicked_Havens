// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/WHCharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

UWHCharacterAttributeSet::UWHCharacterAttributeSet() : Super()
{

}

void UWHCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWHCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWHCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}

void UWHCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWHCharacterAttributeSet, Health, OldHealth);
}

void UWHCharacterAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWHCharacterAttributeSet, Stamina, OldStamina);
}