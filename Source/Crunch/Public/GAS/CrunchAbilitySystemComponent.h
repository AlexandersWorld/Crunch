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
	
private:
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECrunchAbilityInputID,TSubclassOf<UGameplayAbility>> InitialAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECrunchAbilityInputID,TSubclassOf<UGameplayAbility>> Abilities;
};
