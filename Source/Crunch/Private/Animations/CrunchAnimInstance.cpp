#include "Animations/CrunchAnimInstance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/CrunchAbilitySystemStatics.h"

void UCrunchAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
	
	if (UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TryGetPawnOwner()))
	{
		OwnerASC->RegisterGameplayTagEvent(UCrunchAbilitySystemStatics::GetAimStatTag()).AddUObject(this, &UCrunchAnimInstance::OwnerAimTagChanged);
	}
}

void UCrunchAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		FVector Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Length();
		const FRotator BodyRotation = OwnerCharacter->GetActorRotation();
		const FRotator BodyRotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotation, BodyPreviousRotation);
		BodyPreviousRotation = BodyRotation;
		
		YawSpeed = BodyRotationDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
		const FRotator ControlRotation = OwnerCharacter->GetBaseAimRotation();
		LookRotationOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, BodyRotation);
		
		FwdSpeed = Velocity.Dot(ControlRotation.Vector());
		RightSpeed = -Velocity.Dot(ControlRotation.Vector().Cross(FVector::UpVector));
	}
	
	if (OwnerMovementComponent)
	{
		bIsJumping = OwnerMovementComponent->IsFalling();
	}
}

void UCrunchAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}

bool UCrunchAnimInstance::ShouldDoFullBody() const
{
	return (GetSpeed() <= 0) && !(GetIsAiming());
}

void UCrunchAnimInstance::OwnerAimTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bIsAiming = NewCount != 0;
}
