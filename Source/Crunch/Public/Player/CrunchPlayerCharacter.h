// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CrunchCharacter.h"
#include "CrunchPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CRUNCH_API ACrunchPlayerCharacter : public ACrunchCharacter
{
	GENERATED_BODY()

public:
	ACrunchPlayerCharacter();
	
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCam;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GamePlayInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;
};
