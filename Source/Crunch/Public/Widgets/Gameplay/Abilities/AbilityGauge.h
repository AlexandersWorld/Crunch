// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AbilityGauge.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityGauge : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
private:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CooldownCounterText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CooldownDurationText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CostText;
};
