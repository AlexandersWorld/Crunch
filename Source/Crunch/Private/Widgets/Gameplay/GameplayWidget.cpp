// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Gameplay/GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Widgets/UI/ValueGauge.h"
#include "GAS/Attributes/CrunchAttributeSet.h"
#include "Widgets/Gameplay/AbilityListView.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	
	if (OwnerAbilitySystemComponent)
	{
		HealthBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, UCrunchAttributeSet::GetHealthAttribute(), UCrunchAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComponent, UCrunchAttributeSet::GetManaAttribute(), UCrunchAttributeSet::GetMaxManaAttribute());
	}
}

void UGameplayWidget::ConfigureAbilities(const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	AbilityListView->ConfigureAbilities(Abilities);
}