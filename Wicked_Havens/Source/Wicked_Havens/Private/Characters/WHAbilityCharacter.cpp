#include "Characters/WHAbilityCharacter.h"
#include "GameplayAbilities/WHCharacterAttributeSet.h"
#include "GameplayAbilities/WHAbilitySystemComponent.h"

FName AWHAbilityCharacter::AbilitySystemComponentName = FName("AbilitySystemComponent");
FName AWHAbilityCharacter::AttributesName = FName("Attributes");


AWHAbilityCharacter::AWHAbilityCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AbilitySystemComponent  = ObjectInitializer.CreateDefaultSubobject<UWHAbilitySystemComponent>(this, AbilitySystemComponentName);
    Attributes              = ObjectInitializer.CreateDefaultSubobject<UWHCharacterAttributeSet>(this, AttributesName);

    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


}

UAbilitySystemComponent* AWHAbilityCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AWHAbilityCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
            FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}
