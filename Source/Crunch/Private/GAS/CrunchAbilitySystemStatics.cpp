// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CrunchAbilitySystemStatics.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"

FGameplayTag UCrunchAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack");
}

FGameplayTag UCrunchAbilitySystemStatics::GetBasicAttackInputPressedTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack.Pressed");
}

FGameplayTag UCrunchAbilitySystemStatics::GetDeadStatTag()
{
	return FGameplayTag::RequestGameplayTag("Stats.Dead");
}

FGameplayTag UCrunchAbilitySystemStatics::GetStunStatTag()
{
	return FGameplayTag::RequestGameplayTag("Stats.Stun");
}

FGameplayTag UCrunchAbilitySystemStatics::GetAimStatTag()
{
	return FGameplayTag::RequestGameplayTag("Stats.Aim");
}

float UCrunchAbilitySystemStatics::GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability)
{
	float CooldownDuration {0.f};
	
	if (!Ability) return CooldownDuration;
	
	const UGameplayEffect* CooldownEffect = Ability->GetCooldownGameplayEffect();
	if (!CooldownEffect) return CooldownDuration;
	
	CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
	
	return CooldownDuration;
}

float UCrunchAbilitySystemStatics::GetStaticCostForAbility(const UGameplayAbility* Ability)
{
	float Cost {0.f};
	
	if (!Ability) return Cost;
	
	const UGameplayEffect* CostEffect = Ability->GetCostGameplayEffect();
	if (!CostEffect || CostEffect->Modifiers.Num() == 0) return Cost;
	
	CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
	
	return FMath::Abs(Cost);
}
