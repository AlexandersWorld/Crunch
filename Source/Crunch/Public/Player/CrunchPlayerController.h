// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "CrunchPlayerController.generated.h"

class ACrunchPlayerCharacter;
class UGameplayWidget;

/**
 * 
 */
UCLASS()
class CRUNCH_API ACrunchPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	// only called on the client, also on the listening server.
	virtual void AcknowledgePossession(APawn* InPawn) override;
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// only called on the server
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY()
	ACrunchPlayerCharacter* CrunchPlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	UGameplayWidget* GameplayWidget;
	
	void SpawnGameplayWidget();
	
	UPROPERTY(Replicated)
	FGenericTeamId TeamID;
};
