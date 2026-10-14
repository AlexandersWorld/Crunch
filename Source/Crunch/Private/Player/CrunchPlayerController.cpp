
#include "Crunch/Public/Player/CrunchPlayerController.h"
#include "Widgets/Gameplay/GameplayWidget.h"
#include "Net/UnrealNetwork.h"
#include "Player/CrunchPlayerCharacter.h"

void ACrunchPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CrunchPlayerCharacter = Cast<ACrunchPlayerCharacter>(InPawn);
	if (CrunchPlayerCharacter)
	{
		CrunchPlayerCharacter->ServerSideInit();
		CrunchPlayerCharacter->SetGenericTeamId(TeamID);
	}
}

void ACrunchPlayerController::AcknowledgePossession(class APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	CrunchPlayerCharacter = Cast<ACrunchPlayerCharacter>(InPawn);
	if (CrunchPlayerCharacter)
	{
		CrunchPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
}

void ACrunchPlayerController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId ACrunchPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void ACrunchPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACrunchPlayerController, TeamID);
}

void ACrunchPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}
