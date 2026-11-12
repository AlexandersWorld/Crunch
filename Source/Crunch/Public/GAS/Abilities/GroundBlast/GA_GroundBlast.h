// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CrunchGameplayAbilityTypes.h"
#include "GAS/Abilities/CrunchGameplayAbility.h"
#include "GA_GroundBlast.generated.h"

/**
 * 
 */

class ATargetActor_GroundPick;

UCLASS()
class CRUNCH_API UGA_GroundBlast : public UCrunchGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UGA_GroundBlast();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Cue")
	FGameplayTag BlastGameplayCueTag;
	
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TargetAreaRadius {300.f};
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TraceLength {2000.f};
	
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	TSubclassOf<ATargetActor_GroundPick> TargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* TargetingMontage;
		
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* CastMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGenericDamageEffectDef DamageEffectDef;
	
	UFUNCTION()
	void TargetConfirmed(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UFUNCTION()
	void TargetCanceled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
