// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AbilityGauge.generated.h"

class UGameplayAbility;
class UImage;
class UTextBlock;

USTRUCT(BlueprintType)
struct FAbilityWidgetData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityGauge : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	void ConfigureWithWidgetData(const FAbilityWidgetData* WidgetData);
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Visial")
	FName IconMaterialParamName {"Icon"};
	
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CooldownCounterText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CooldownDurationText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CostText;
};
