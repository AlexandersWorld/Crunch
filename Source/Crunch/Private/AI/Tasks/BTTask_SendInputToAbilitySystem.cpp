// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTTask_SendInputToAbilitySystem.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

EBTNodeResult::Type UBTTask_SendInputToAbilitySystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AAIController* OwnerAIC = OwnerComp.GetAIOwner())
	{
		if (UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerAIC->GetPawn()))
		{
			OwnerASC->PressInputID(static_cast<int32>(InputID));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
