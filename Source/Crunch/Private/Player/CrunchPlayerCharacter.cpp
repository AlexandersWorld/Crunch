// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CrunchPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACrunchPlayerCharacter::ACrunchPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	
	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Camera");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void ACrunchPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (APlayerController* OwningPlayerController = GetController<APlayerController>())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
			OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSubsystem->RemoveMappingContext(GamePlayInputMappingContext);
			InputSubsystem->AddMappingContext(GamePlayInputMappingContext, 0);
		}
	}
}

void ACrunchPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACrunchPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACrunchPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACrunchPlayerCharacter::HandleMoveInput);
		
		for (const TPair<ECrunchAbilityInputID, UInputAction*>& Pair : GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(Pair.Value, ETriggerEvent::Triggered, this, &ACrunchPlayerCharacter::HandleAbilityInput, Pair.Key);
		}
	}
}

void ACrunchPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	const FVector2D InputValue = InputActionValue.Get<FVector2D>();
	
	AddControllerPitchInput(-InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ACrunchPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	InputValue.Normalize();
	
	AddMovementInput(GetMoveForwardDirection() * InputValue.Y + GetLookRightDirection() * InputValue.X);
}

void ACrunchPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue,
	ECrunchAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}

void ACrunchPlayerCharacter::OnDead()
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		DisableInput(PlayerController);
	}
}

void ACrunchPlayerCharacter::OnRespawn()
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		EnableInput(PlayerController);
	}
}

FVector ACrunchPlayerCharacter::GetLookRightDirection() const
{
	return ViewCam->GetRightVector();
}

FVector ACrunchPlayerCharacter::GetLookForwardDirection() const
{
	return ViewCam->GetForwardVector();
}

FVector ACrunchPlayerCharacter::GetMoveForwardDirection() const
{
	return FVector::CrossProduct(GetLookRightDirection(), FVector::UpVector);
}
