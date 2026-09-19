#include "Animations/CrunchAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCrunchAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	
	if (OwnerCharacter)
	{
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UCrunchAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
}

void UCrunchAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
