
#include "Crunch/Public/Character/CrunchCharacter.h"
#include "Components/SkeletalMeshComponent.h"

ACrunchCharacter::ACrunchCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACrunchCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACrunchCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
