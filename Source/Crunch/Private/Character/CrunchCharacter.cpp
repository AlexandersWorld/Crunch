
#include "Crunch/Public/Character/CrunchCharacter.h"
#include "GAS/CrunchAbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attributes/CrunchAttributeSet.h"
#include "GAS/CrunchAbilitySystemStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widgets/Gameplay/OverHeadStatsGauge.h"
#include "Kismet/GameplayStatics.h"

ACrunchCharacter::ACrunchCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CrunchAbilitySystemComponent = CreateDefaultSubobject<UCrunchAbilitySystemComponent>("Crunch AbilitySystem Component");
	CrunchAttributeSet = CreateDefaultSubobject<UCrunchAttributeSet>("Crunch Attribute Set");
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Over Head Widget Component");
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
	BindGASChangedDelegates();
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

void ACrunchCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (IsValid(NewController) && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

void ACrunchCharacter::ServerSideInit()
{
	CrunchAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CrunchAbilitySystemComponent->ApplyInitialEffects();
	CrunchAbilitySystemComponent->GiveInitialAbilities();
}

void ACrunchCharacter::ClientSideInit()
{
	CrunchAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

bool ACrunchCharacter::IsLocallyControlledByPlayer() const
{
	return GetController() && GetController()->IsLocalPlayerController();
}

UAbilitySystemComponent* ACrunchCharacter::GetAbilitySystemComponent() const
{
	return CrunchAbilitySystemComponent;
}

void ACrunchCharacter::BindGASChangedDelegates()
{
	if (CrunchAbilitySystemComponent)
	{
		CrunchAbilitySystemComponent->RegisterGameplayTagEvent(UCrunchAbilitySystemStatics::GetDeadStatTag()).AddUObject(this, &ACrunchCharacter::DeathTagUpdated);
	}
}

void ACrunchCharacter::DeathTagUpdated(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount != 0)
	{
		StartDeathSequence();
	}
	else
	{
		Respawn();
	}
}

void ACrunchCharacter::ConfigureOverHeadStatusWidget()
{
	if (!IsValid(OverHeadWidgetComponent)) return;
	
	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	
	UOverHeadStatsGauge* OverheadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (IsValid(OverheadStatsGauge))
	{
		OverheadStatsGauge->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);
		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityUpdateTimerHandle, this,
		&ACrunchCharacter::UpdateHeadGaugeVisibility,
		HeadStatGaugeVisibilityCheckUpdateGap,
		true
		);
	}
}

void ACrunchCharacter::SetStatusGaugeEnable(bool bIsEnabled)
{
	GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
	if (bIsEnabled)
	{
		ConfigureOverHeadStatusWidget();	
	}
	else
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
	}
}

void ACrunchCharacter::PlayDeathAnimation()
{
	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
}

void ACrunchCharacter::UpdateHeadGaugeVisibility() const
{
	const APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (IsValid(LocalPlayerPawn))
	{
		const float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > HeadStatGaugeVisibilityRangeSquared);
	}	
}

void ACrunchCharacter::StartDeathSequence()
{
	OnDead();
	PlayDeathAnimation();
	SetStatusGaugeEnable(false);
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACrunchCharacter::Respawn()
{
	OnRespawn();
	UE_LOG(LogTemp, Warning, TEXT("Respawn"));
}

void ACrunchCharacter::OnDead()
{
}

void ACrunchCharacter::OnRespawn()
{
}
