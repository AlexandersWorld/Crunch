#include "AI/CrunchAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/CrunchAbilitySystemStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ACrunchAIController::ACrunchAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	
	SightConfig->SetMaxAge(5.f);
	
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACrunchAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ACrunchAIController::TargetPerceptionForgotten);
}

void ACrunchAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}

void ACrunchAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (IGenericTeamAgentInterface* PawnTeamInterface = Cast<IGenericTeamAgentInterface>(InPawn))
	{
		SetGenericTeamId(PawnTeamInterface->GetGenericTeamId());
		ClearAndDisableAllSenses();
		EnableAllSenses();
	}
	
	if (UAbilitySystemComponent* PawnASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InPawn))
	{
		PawnASC->RegisterGameplayTagEvent(UCrunchAbilitySystemStatics::GetDeadStatTag())
			.AddUObject(this, &ACrunchAIController::PawnDeadTagUpdated);
	}
}

void ACrunchAIController::TargetPerceptionUpdated(AActor* TargetActor,FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!GetCurrentTarget())
		{
			SetCurrentTarget(TargetActor);
		}
	}
	else
	{
		ForgetActorIfDead(TargetActor);
	}
}

void ACrunchAIController::TargetPerceptionForgotten(AActor* ForgottenActor)
{
	if (!ForgottenActor) return;
	
	if (GetCurrentTarget() == ForgottenActor)
	{
		SetCurrentTarget(GetNextPerceivedActor());
	}
}

const UObject* ACrunchAIController::GetCurrentTarget() const
{
	if (const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		return BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName);
	}
	return nullptr;
}

void ACrunchAIController::SetCurrentTarget(AActor* NewTarget)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent) return;
	
	if (NewTarget)
	{
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, NewTarget);	
	}
	else
	{
		BlackboardComponent->ClearValue(TargetBlackboardKeyName);
	}
}

AActor* ACrunchAIController::GetNextPerceivedActor() const
{
	if (PerceptionComponent)
	{
		TArray<AActor*> Actors;
		AIPerceptionComponent->GetPerceivedHostileActors(Actors);
		
		if (Actors.Num() != 0)
		{
			return Actors[0];
		}
	}
	return nullptr;
}

void ACrunchAIController::ForgetActorIfDead(AActor* ActorToForget)
{
	if (const UAbilitySystemComponent* ActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorToForget))
	{
		if (ActorASC->HasMatchingGameplayTag(UCrunchAbilitySystemStatics::GetDeadStatTag()))
		{
			for (UAIPerceptionComponent::TActorPerceptionContainer::TIterator It = AIPerceptionComponent->GetPerceptualDataIterator(); It; ++It)
			{
				if (It->Key != ActorToForget) continue;
				
				for (FAIStimulus& Stimulus : It->Value.LastSensedStimuli)
				{
					Stimulus.SetStimulusAge(TNumericLimits<float>::Max());
				}
			}
		}
	}
}

void ACrunchAIController::ClearAndDisableAllSenses()
{
	AIPerceptionComponent->AgeStimuli(TNumericLimits<float>::Max());
	
	for (auto SenseConfigIt = AIPerceptionComponent->GetSensesConfigIterator(); SenseConfigIt; ++SenseConfigIt)
	{
		AIPerceptionComponent->SetSenseEnabled((*SenseConfigIt)->GetSenseImplementation(), false);
	}
	
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
	}
}

void ACrunchAIController::EnableAllSenses()
{
	for (auto SenseConfigIT = AIPerceptionComponent->GetSensesConfigIterator(); SenseConfigIT; ++SenseConfigIT)
	{
		AIPerceptionComponent->SetSenseEnabled((*SenseConfigIT)->GetSenseImplementation(), true);
	}
}

void ACrunchAIController::PawnDeadTagUpdated(const FGameplayTag Tag, int32 Count)
{
	if (Count != 0)
	{
		GetBrainComponent()->StopLogic("Dead");
		ClearAndDisableAllSenses();
	}
	else
	{
		GetBrainComponent()->StartLogic();
		EnableAllSenses();
	}
}
