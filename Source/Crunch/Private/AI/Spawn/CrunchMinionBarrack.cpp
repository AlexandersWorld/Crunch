// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Spawn/CrunchMinionBarrack.h"

#include "AI/Minion/CrunchMinion.h"
#include "GameFramework/PlayerStart.h"

ACrunchMinionBarrack::ACrunchMinionBarrack()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACrunchMinionBarrack::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SpawnNewMinions(5);
	}
}

const APlayerStart* ACrunchMinionBarrack::GetNextSpawnSpot()
{
	if (SpawnSpot.Num() == 0)
	{
		return nullptr;
	}
	
	++NextSpawnSpotIndex;
	
	if (NextSpawnSpotIndex >= SpawnSpot.Num())
	{
		NextSpawnSpotIndex = 0;
	}
	
	return SpawnSpot[NextSpawnSpotIndex];
}

void ACrunchMinionBarrack::SpawnNewMinions(int Amt)
{
	for (int i=0; i<Amt; i++)
	{
		FTransform SpawnTransform = GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
		{
			SpawnTransform = NextSpawnSpot->GetActorTransform();
		}
		ACrunchMinion* NewMinion = GetWorld()->SpawnActorDeferred<ACrunchMinion>(MinionClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		NewMinion->SetGenericTeamId(BarrackTeamId);
		NewMinion->FinishSpawning(SpawnTransform);
		MinionPool.Add(NewMinion);
	}
}
