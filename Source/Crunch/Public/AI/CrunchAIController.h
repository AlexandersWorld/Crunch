// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CrunchAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;
struct FAIStimulus;

UCLASS()
class CRUNCH_API ACrunchAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACrunchAIController();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	FName TargetBlackboardKeyName {"Target"};
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAISenseConfig_Sight* SightConfig;
	
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor,FAIStimulus Stimulus);
	
	UFUNCTION()
	void TargetPerceptionForgotten(AActor* ForgottenActor);
	
	const UObject* GetCurrentTarget() const;
	void SetCurrentTarget(AActor* NewTarget);
	
	AActor* GetNextPerceivedActor() const;
};
