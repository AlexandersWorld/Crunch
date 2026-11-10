// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TargetActor_GroundPick.generated.h"

/**
 * 
 */
UCLASS()
class  ATargetActor_GroundPick : public AGameplayAbilityTargetActor
{

	GENERATED_BODY()
	
public:
	ATargetActor_GroundPick();
	virtual void Tick(float DeltaTime) override;
private:
	FVector GetTargetPoint() const;
	
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TraceLength {2000.f};
};
