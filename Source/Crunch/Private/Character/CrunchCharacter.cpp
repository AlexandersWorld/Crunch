
#include "Crunch/Public/Character/CrunchCharacter.h"
#include "GAS/CrunchAbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GAS/Attributes/CrunchAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widgets/Gameplay/OverHeadStatsGauge.h"

ACrunchCharacter::ACrunchCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CrunchAbilitySystemComponent = CreateDefaultSubobject<UCrunchAbilitySystemComponent>("Crunch AbilitySystem Component");
	CrunchAttributeSet = CreateDefaultSubobject<UCrunchAttributeSet>("Crunch Attribute Set");
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Over Head Widget Component");
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void ACrunchCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConfigureOverHeadStatusWidget();
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

void ACrunchCharacter::ConfigureOverHeadStatusWidget()
{
	if (!IsValid(OverHeadWidgetComponent)) return;
	
	UOverHeadStatsGauge* OverheadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (IsValid(OverheadStatsGauge))
	{
		OverheadStatsGauge->ConfigureWithASC(GetAbilitySystemComponent());
	}
}
