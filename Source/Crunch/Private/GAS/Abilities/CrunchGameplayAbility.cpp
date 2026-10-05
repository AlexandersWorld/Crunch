// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/CrunchGameplayAbility.h"
#include "Components/SkeletalMeshComponent.h"

UAnimInstance* UCrunchGameplayAbility::GetOwnerAnimInstance() const
{
	if (const USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}
