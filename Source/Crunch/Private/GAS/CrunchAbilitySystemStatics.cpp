// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CrunchAbilitySystemStatics.h"
#include "GameplayTagContainer.h"

FGameplayTag UCrunchAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack");
}

FGameplayTag UCrunchAbilitySystemStatics::GetDeadStatTag()
{
	return FGameplayTag::RequestGameplayTag("Stats.Dead");
}
