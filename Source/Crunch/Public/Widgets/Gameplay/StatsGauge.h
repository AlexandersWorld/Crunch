// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Widgets/CrunchUserWidget.h"
#include "StatsGauge.generated.h"

class UImage;
class UTextBlock;
struct FOnAttributeChangeData;

/**
 * 
 */
UCLASS()
class CRUNCH_API UStatsGauge : public UCrunchUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AttributeText;

	UPROPERTY(EditAnywhere, Category="Visual")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, Category="Visual")
	UTexture2D* IconTexture;
	
	void SetValue(float NewValue);
	
	FNumberFormattingOptions NumberFormatingOptions;
	
	void AttributeChanged(const FOnAttributeChangeData& Data);
};
