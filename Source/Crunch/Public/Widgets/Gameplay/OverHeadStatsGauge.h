// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CrunchUserWidget.h"
#include "OverHeadStatsGauge.generated.h"

class UAbilitySystemComponent;
class UValueGauge;

UCLASS()
class CRUNCH_API UOverHeadStatsGauge : public UCrunchUserWidget
{
	GENERATED_BODY()
	
public:
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent);
	
	UPROPERTY(meta=(BindWidget))
	UValueGauge* HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	UValueGauge* ManaBar;
};
