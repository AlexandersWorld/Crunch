// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CrunchPlayerController.generated.h"

class ACrunchPlayerCharacter;
class UGameplayWidget;

/**
 * 
 */
UCLASS()
class CRUNCH_API ACrunchPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// only called on the client, also on the listening server.
	virtual void AcknowledgePossession(class APawn* InPawn) override;
	
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
};
