// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CrunchUserWidget.h"
#include "ValueGauge.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class CRUNCH_API UValueGauge : public UCrunchUserWidget
{
	GENERATED_BODY()
	
public:
	void SetValue(float NewValue, float NewMaxValue) const;

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* ValueText;
};
