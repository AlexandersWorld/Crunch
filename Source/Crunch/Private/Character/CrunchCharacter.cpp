
#include "Crunch/Public/Character/CrunchCharacter.h"
#include "GAS/CrunchAbilitySystemComponent.h"
#include "GAS/Attributes/CrunchAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"

ACrunchCharacter::ACrunchCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CrunchAbilitySystemComponent = CreateDefaultSubobject<UCrunchAbilitySystemComponent>("Crunch AbilitySystem Component");
	CrunchAttributeSet = CreateDefaultSubobject<UCrunchAttributeSet>("Crunch Attribute Set");
}

void ACrunchCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACrunchCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrunchCharacter::ServerSideInit()
{
	CrunchAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CrunchAbilitySystemComponent->ApplyInitialEffects();
}

void ACrunchCharacter::ClientSideInit()
{
	CrunchAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ACrunchCharacter::GetAbilitySystemComponent() const
{
	return CrunchAbilitySystemComponent;
}
