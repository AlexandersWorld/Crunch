// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Gameplay/AbilityListView.h"
#include "Widgets/Gameplay/Abilities/AbilityGauge.h"

void UAbilityListView::ConfigureAbilities(const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	OnEntryWidgetGenerated().AddUObject(this, &UAbilityListView::AbilityGaugeGenerated);
	for (const auto& AbilityPair : Abilities)
	{
		AddItem(AbilityPair.Value.GetDefaultObject());
	}
}

void UAbilityListView::AbilityGaugeGenerated(UUserWidget& Widget)
{
	if (UAbilityGauge* AbilityGauge = Cast<UAbilityGauge>(&Widget))
	{
		AbilityGauge->ConfigureWithWidgetData(FindWidgetDataForAbility(
			AbilityGauge->GetListItem<UGameplayAbility>()->GetClass()
		));
	}
}

const struct FAbilityWidgetData* UAbilityListView::FindWidgetDataForAbility(
	const TSubclassOf<UGameplayAbility> AbilityClass) const
{
	if (!AbilityDataTable) return nullptr;
	
	for (auto& AbilityWidgetDataPair : AbilityDataTable->GetRowMap())
	{
		const FAbilityWidgetData* WidgetData = AbilityDataTable->FindRow<FAbilityWidgetData>(AbilityWidgetDataPair.Key, "");
		if (WidgetData && WidgetData->AbilityClass == AbilityClass)
		{
			return WidgetData;
		}
	}
	return nullptr;
}
