// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/CrunchGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Combo : public UCrunchGameplayAbility
{
	GENERATED_BODY()
	
	
public:
	
protected:
	UGA_Combo();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	static FGameplayTag GetComboChangedEventTag();
	static FGameplayTag GetComboChangedEventEndTag();
	static FGameplayTag GetComboTargetEventTag();
private:
	void SetupWaitComboInputPress();
	
	UFUNCTION()
	void HandleInputPress(float TimeWaited);
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* ComboMontage;
	
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float TargetSweepSphereRadius;
	
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;
	
	void TryCommitCombo();
	
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Data);
	
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);
	
	FName NextComboName;
};
