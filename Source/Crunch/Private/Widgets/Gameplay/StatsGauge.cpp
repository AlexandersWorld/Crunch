// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/Gameplay/StatsGauge.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UStatsGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	Icon->SetBrushFromTexture(IconTexture);
}

void UStatsGauge::NativeConstruct()
{
	Super::NativeConstruct();
	
	NumberFormatingOptions.MaximumFractionalDigits = 0;
	
	if (APawn* OwnerPlayerPawn = GetOwningPlayerPawn())
	{
		if (UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn()))
		{
			bool bFound {false};
			float AttributeValue = OwnerASC->GetGameplayAttributeValue(Attribute, bFound);
			SetValue(AttributeValue);
			
			OwnerASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UStatsGauge::AttributeChanged);
		}
	};
}

void UStatsGauge::AttributeChanged(const FOnAttributeChangeData& Data)
{
	SetValue(Data.NewValue);
}

void UStatsGauge::SetValue(float NewValue)
{
	AttributeText->SetText(FText::AsNumber(NewValue, &NumberFormatingOptions));
}
