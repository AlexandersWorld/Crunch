// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CrunchCharacter.generated.h"

class UCrunchAbilitySystemComponent;
class UCrunchAttributeSet;

UCLASS()
class CRUNCH_API ACrunchCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACrunchCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*GAMEPLAY ABILITY SYSTEM START*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*GAMEPLAY ABILITY SYSTEM END*/
	
	
	
protected:
	
	
private:
	UPROPERTY()
	UCrunchAbilitySystemComponent* CrunchAbilitySystemComponent;
	
	UPROPERTY()
	UCrunchAttributeSet* CrunchAttributeSet;
};
