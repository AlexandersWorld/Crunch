#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CrunchAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class CRUNCH_API UCrunchAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;
};
