// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CrunchUserWidget.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "ValueGauge.generated.h"

class UProgressBar;
class UTextBlock;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CRUNCH_API UValueGauge : public UCrunchUserWidget
{
	GENERATED_BODY()
	
public:
	void SetValue(float NewValue, float NewMaxValue);
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);

protected:
	virtual void NativeConstruct() override;
	
private:
	float CachedValue;
	float CachedMaxValue;
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* ValueText;
	
	void ValueChanged(const FOnAttributeChangeData& ChangedData);
	void MaxValueChanged(const FOnAttributeChangeData& ChangedData);
};
