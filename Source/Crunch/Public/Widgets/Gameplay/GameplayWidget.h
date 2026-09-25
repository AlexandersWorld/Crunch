// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CrunchUserWidget.h"
#include "GameplayWidget.generated.h"

class UValueGauge;

/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayWidget : public UCrunchUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	UValueGauge* HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	UValueGauge* ManaBar;
};
