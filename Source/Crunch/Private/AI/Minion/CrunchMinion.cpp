// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Minion/CrunchMinion.h"

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

