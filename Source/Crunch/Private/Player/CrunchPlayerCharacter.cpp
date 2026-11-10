// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CrunchPlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Crunch/Crunch.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/CrunchAbilitySystemStatics.h"

ACrunchPlayerCharacter::ACrunchPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->ProbeChannel = ECC_SpringArm;
	
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

void ACrunchPlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, ECrunchAbilityInputID InputID)
{
	if (InputActionValue.Get<bool>())
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
	if (InputID == ECrunchAbilityInputID::BasicAttack)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, UCrunchAbilitySystemStatics::GetBasicAttackInputPressedTag(), FGameplayEventData());
		Server_SendGameplayEventToSelf(UCrunchAbilitySystemStatics::GetBasicAttackInputPressedTag(), FGameplayEventData());
	}
}

void ACrunchPlayerCharacter::SetInputEnabledFromPlayerController(const bool bEnabled)
{
	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		if (bEnabled)
		{
			EnableInput(PlayerController);
		}
		else
		{
			DisableInput(PlayerController);
		}
	}
}

void ACrunchPlayerCharacter::OnDead()
{
	SetInputEnabledFromPlayerController(false);
}

void ACrunchPlayerCharacter::OnRespawn()
{
	SetInputEnabledFromPlayerController(true);
}

void ACrunchPlayerCharacter::OnStun()
{
	SetInputEnabledFromPlayerController(false);
}

void ACrunchPlayerCharacter::OnRecoverFromStun()
{
	if (IsDead()) return;
	SetInputEnabledFromPlayerController(true);
}

void ACrunchPlayerCharacter::OnAimStageChanged(bool bIsAiming)
{
	LerpCameraToLocalOffsetLocation(bIsAiming ? CameraAimLocalOffset : FVector{0.f});
}

void ACrunchPlayerCharacter::LerpCameraToLocalOffsetLocation(const FVector& Goal)
{
	GetWorldTimerManager().ClearTimer(CameraLerpTimerHandle);
	GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ACrunchPlayerCharacter::TickCameraLocalOffsetLerp, Goal));
}

void ACrunchPlayerCharacter::TickCameraLocalOffsetLerp(FVector Goal)
{
	FVector CurrentLocalOffset = ViewCam->GetRelativeLocation();
	if (FVector::Dist(CurrentLocalOffset, Goal) < 1.f)
	{
		ViewCam->SetRelativeLocation(Goal);
		return;
	}
	
	float LerpAlpha = FMath::Clamp(GetWorld()->GetDeltaSeconds() * CameraLerpSpeed, 0.f, 1.f);
	FVector NewLocalOffset = FMath::Lerp(CurrentLocalOffset, Goal, LerpAlpha);
	ViewCam->SetRelativeLocation(NewLocalOffset);
	
	GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ACrunchPlayerCharacter::TickCameraLocalOffsetLerp, Goal));
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
