// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Gameplay/AbilityListView.h"

void UAbilityListView::ConfigureAbilities(const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const auto& AbilityPair : Abilities)
	{
		AddItem(AbilityPair.Value.GetDefaultObject());
	}
}
