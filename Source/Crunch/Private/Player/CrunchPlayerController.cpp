
#include "Crunch/Public/Player/CrunchPlayerController.h"
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
	}
}
