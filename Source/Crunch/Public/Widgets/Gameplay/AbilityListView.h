// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/CrunchGameplayAbilityTypes.h"
#include "AbilityListView.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityListView : public UListView
{
	GENERATED_BODY()
	
public:
	void ConfigureAbilities(const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);

};
