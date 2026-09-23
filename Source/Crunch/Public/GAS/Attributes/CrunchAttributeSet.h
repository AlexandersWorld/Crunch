// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CrunchAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class CRUNCH_API UCrunchAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	ATTRIBUTE_ACCESSORS(UCrunchAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCrunchAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UCrunchAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UCrunchAttributeSet, MaxMana);
	
private:
	UPROPERTY()
	FGameplayAttributeData Health;
	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	UPROPERTY()
	FGameplayAttributeData Mana;
	UPROPERTY()
	FGameplayAttributeData MaxMana;
};
