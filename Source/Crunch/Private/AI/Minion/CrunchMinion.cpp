// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Minion/CrunchMinion.h"

#include "AbilitySystemComponent.h"
#include "GAS/CrunchAbilitySystemStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void ACrunchMinion::SetGoal(AActor* Goal) const
{
	if (AAIController* AIController = GetController<AAIController>())
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(GoalBlackboardKeyName, Goal);
		}
	}
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

