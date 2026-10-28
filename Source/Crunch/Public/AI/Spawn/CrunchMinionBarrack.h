// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "CrunchMinionBarrack.generated.h"

class ACrunchMinion;
class APlayerStart;

UCLASS()
class CRUNCH_API ACrunchMinionBarrack : public AActor
{
	GENERATED_BODY()

public:
	ACrunchMinionBarrack();

	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamId;
	
	UPROPERTY()
	TArray<ACrunchMinion*> MinionPool;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ACrunchMinion> MinionClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<APlayerStart*> SpawnSpot;
	
	int NextSpawnSpotIndex = -1;
	
	const APlayerStart* GetNextSpawnSpot();
	
	void SpawnNewMinions(int Amt);
};
