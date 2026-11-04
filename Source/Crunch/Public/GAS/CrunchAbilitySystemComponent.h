// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "CrunchGameplayAbilityTypes.h"
#include "CrunchAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UCrunchAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UCrunchAbilitySystemComponent();
	void ApplyInitialEffects();
	void GiveInitialAbilities();
	void ApplyFullStatEffect();
	
	// Get the Abilities that is unique for the avatar actor, this do not include generic/basic ones
	const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;
	
private:
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level = 1);
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> FullStatEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECrunchAbilityInputID,TSubclassOf<UGameplayAbility>> InitialAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECrunchAbilityInputID,TSubclassOf<UGameplayAbility>> Abilities;
};
