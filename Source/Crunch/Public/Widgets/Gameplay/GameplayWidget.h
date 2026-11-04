// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CrunchGameplayAbilityTypes.h"
#include "Widgets/CrunchUserWidget.h"
#include "GameplayWidget.generated.h"

class UValueGauge;
class UGameplayAbility;
class UAbilityListView;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayWidget : public UCrunchUserWidget
{
	GENERATED_BODY()
	
public:
	void ConfigureAbilities(const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	UValueGauge* HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	UValueGauge* ManaBar;
	
	UPROPERTY(meta=(BindWidget))
	UAbilityListView* AbilityListView;
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
