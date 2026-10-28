// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Minion/CrunchMinion.h"

#include "AbilitySystemComponent.h"
#include "GAS/CrunchAbilitySystemStatics.h"

ACrunchMinion::ACrunchMinion()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACrunchMinion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACrunchMinion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBasedOnTeamID();
}

bool ACrunchMinion::IsActive() const
{
	return !GetAbilitySystemComponent()->HasMatchingGameplayTag(
		UCrunchAbilitySystemStatics::GetDeadStatTag());
}

void ACrunchMinion::Activate() const
{
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(
		FGameplayTagContainer(UCrunchAbilitySystemStatics::GetDeadStatTag()));
}

void ACrunchMinion::PickSkinBasedOnTeamID()
{
	if (USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId()))
	{
		GetMesh()->SetSkeletalMesh(*Skin);	
	}
}

void ACrunchMinion::OnRep_TeamID()
{
	PickSkinBasedOnTeamID();
}

