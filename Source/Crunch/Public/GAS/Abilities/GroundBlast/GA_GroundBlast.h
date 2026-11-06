// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/CrunchGameplayAbility.h"
#include "GA_GroundBlast.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_GroundBlast : public UCrunchGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UGA_GroundBlast();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* GroundBlastMontage;
};
