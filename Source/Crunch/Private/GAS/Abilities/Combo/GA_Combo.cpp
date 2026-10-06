// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Combo/GA_Combo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameplayTagsManager.h"
#include "GAS/CrunchAbilitySystemStatics.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(UCrunchAbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UCrunchAbilitySystemStatics::GetBasicAttackAbilityTag());
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
		
		UAbilityTask_WaitGameplayEvent* WaitComboChangedEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, GetComboChangedEventTag()
			, nullptr
			, false
			, false);
		
		WaitComboChangedEventTask->EventReceived.AddDynamic(this, &UGA_Combo::ComboChangedEventReceived);
		WaitComboChangedEventTask->ReadyForActivation();
	}
	
	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitTargetingEvent = 
			UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetComboTargetEventTag());
		WaitTargetingEvent->EventReceived.AddDynamic(this, &UGA_Combo::DoDamage);
		WaitTargetingEvent->ReadyForActivation();
		
	}
	
	SetupWaitComboInputPress();
}

FGameplayTag UGA_Combo::GetComboChangedEventTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change");
}

FGameplayTag UGA_Combo::GetComboChangedEventEndTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Change.End");
}

FGameplayTag UGA_Combo::GetComboTargetEventTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Combo.Damage");
}

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddDynamic(this, &UGA_Combo::HandleInputPress);
	WaitInputPress->ReadyForActivation();
}

void UGA_Combo::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

void UGA_Combo::TryCommitCombo()
{
	UAnimInstance* OwerAnimInstance = GetOwnerAnimInstance();
	
	if (NextComboName == NAME_None) return;
	if (!IsValid(OwerAnimInstance)) return;
	
	OwerAnimInstance->Montage_SetNextSection(OwerAnimInstance->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;
	
	if (EventTag == GetComboChangedEventEndTag())
	{
		NextComboName = NAME_None;
		UE_LOG(LogTemp, Warning, TEXT("next combo is cleared"));
		return;
	}
	
	TArray<FName> TagNames; 
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();
	
	UE_LOG(LogTemp, Warning, TEXT("next combo is now %s"), *NextComboName.ToString());
}

void UGA_Combo::DoDamage(FGameplayEventData Data)
{
	TArray<FHitResult> HitResult = GetHitResultFromSweepLocationTargetData(Data.TargetData, 30.f, true, true);
}
