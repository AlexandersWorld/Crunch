// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GAS/CrunchGameplayAbilityTypes.h"
#include "CrunchCharacter.generated.h"

class UCrunchAbilitySystemComponent;
class UCrunchAttributeSet;
class UWidgetComponent;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class CRUNCH_API ACrunchCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	/*GAMEPLAY ABILITY SYSTEM START*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*GAMEPLAY ABILITY SYSTEM END*/
	
	bool IsDead() const;
	void RespawnImmediately();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendGameplayEventToSelf(const FGameplayTag& EventTag, const FGameplayEventData& EventData);
	const TMap<ECrunchAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;
private:
	void BindGASChangedDelegates();
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void StunTagUpdated(const FGameplayTag Tag, int32 NewCount);
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DeathMontageFinishedTimeShift {-0.8f};
	
	FTimerHandle DeathMontageTimerHandle;
	
	FTransform MeshRelativeTransform;
	
	void DeathMontageFinished();
	void SetRagdollEnabled(bool bIsEnabled);
	
	void SetStatusGaugeEnable(bool bIsEnabled);
	void PlayDeathAnimation();
	void UpdateHeadGaugeVisibility() const;
	void StartDeathSequence();
	void Respawn();
	
	virtual void OnDead();
	virtual void OnRespawn();
	
	UPROPERTY(ReplicatedUsing = OnRep_TeamID)
	FGenericTeamId TeamID;
	
	UFUNCTION()
	virtual void OnRep_TeamID();
	
	void SetAIPerceptionStimuliSourceEnabled(bool bIsEnabled);
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Stun")
	UAnimMontage* StunMontage;
	
	virtual void OnStun();
	virtual void OnRecoverFromStun();
};
