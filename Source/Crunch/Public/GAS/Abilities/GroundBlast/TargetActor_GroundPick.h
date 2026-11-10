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
	virtual void ConfirmTargetingAndContinue() override;
	void SetTargetOptions(bool bTargetFriendly, bool bTargetEnemy = true);
	void SetTargetAreaRadius(float NewRadius);
	
	FORCEINLINE void SetTraceRangeLength(float TraceRangeLength) { TraceLength = TraceRangeLength; }
	FORCEINLINE void SetShouldDrawDebug(bool bDrawDebug) { bShouldDrawDebug = bDrawDebug; }
private:
	FVector GetTargetPoint() const;
	
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TargetAreaRadius {300.f};
	
	UPROPERTY(EditDefaultsOnly, Category="Targeting")
	float TraceLength {2000.f};
	
	bool bShouldTargetEnemy {true};
	bool bShouldTargetFriendly {false};
	
	bool bShouldDrawDebug {false};
};
