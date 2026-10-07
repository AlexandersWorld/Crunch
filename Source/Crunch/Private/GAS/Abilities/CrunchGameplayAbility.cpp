// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/CrunchGameplayAbility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UAnimInstance* UCrunchGameplayAbility::GetOwnerAnimInstance() const
{
	if (const USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}

TArray<FHitResult> UCrunchGameplayAbility::GetHitResultFromSweepLocationTargetData(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, bool bDrawDebug,
	bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	TSet<AActor*> HitActors;
	
	for (const TSharedPtr<FGameplayAbilityTargetData> TargetData : TargetDataHandle.Data)
	{
		const FVector StartLocation = TargetData->GetOrigin().GetTranslation();
		const FVector EndLocation = TargetData->GetEndPoint();
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		TArray<AActor*> ActorsToIgnore;
		
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}
		
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
		TArray<FHitResult> Results;
		
		UKismetSystemLibrary::SphereTraceMultiForObjects(
			this,
			StartLocation,
			EndLocation,
			SphereSweepRadius,
			ObjectTypes,
			false,
			ActorsToIgnore,
			DrawDebugTrace,
			Results,
			false);
		
		for (const FHitResult& Result : Results)
		{
			if (HitActors.Contains(Result.GetActor())) continue;
			
			HitActors.Add(Result.GetActor());
			OutResults.Add(Result);
		}
	}
	return OutResults;
}
