
#include "Crunch/Public/Player/CrunchPlayerController.h"
#include "Widgets/Gameplay/GameplayWidget.h"
#include "Player/CrunchPlayerCharacter.h"

void ACrunchPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CrunchPlayerCharacter = Cast<ACrunchPlayerCharacter>(InPawn);
	if (CrunchPlayerCharacter)
	{
		CrunchPlayerCharacter->ServerSideInit();
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

void ACrunchPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}
