// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CrunchCharacter.generated.h"

class UCrunchAbilitySystemComponent;
class UCrunchAttributeSet;
class UWidgetComponent;

UCLASS()
class CRUNCH_API ACrunchCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACrunchCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;

	/*GAMEPLAY ABILITY SYSTEM START*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*GAMEPLAY ABILITY SYSTEM END*/
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCrunchAbilitySystemComponent* CrunchAbilitySystemComponent;
	
	UPROPERTY()
	UCrunchAttributeSet* CrunchAttributeSet;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Gameplay Ability")
	UWidgetComponent* OverHeadWidgetComponent;
	
	void ConfigureOverHeadStatusWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
	
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;
	
	void UpdateHeadGaugeVisibility() const;
};
