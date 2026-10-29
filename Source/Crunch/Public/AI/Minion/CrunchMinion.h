// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CrunchCharacter.h"
#include "CrunchMinion.generated.h"

UCLASS()
class CRUNCH_API ACrunchMinion : public ACrunchCharacter
{
	GENERATED_BODY()

public:
	ACrunchMinion();
	virtual void BeginPlay() override;

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	bool IsActive() const;
	void Activate();
	void SetGoal(AActor* Goal) const;
protected:

public:
	void PickSkinBasedOnTeamID();
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TMap<FGenericTeamId, USkeletalMesh*> SkinMap;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName GoalBlackboardKeyName {"Goal"};
private:
	virtual void OnRep_TeamID() override;
};
