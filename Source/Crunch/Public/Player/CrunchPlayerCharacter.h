// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/CrunchCharacter.h"
#include "GAS/CrunchGameplayAbilityTypes.h"
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
	
	FVector GetLookRightDirection() const;
	FVector GetLookForwardDirection() const;
	FVector GetMoveForwardDirection() const;
	
private:
	/**********************************************************/	
	/*                           Input                        */
	/**********************************************************/	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GamePlayInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;
		
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECrunchAbilityInputID, UInputAction*> GameplayAbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECrunchAbilityInputID InputID);

};
