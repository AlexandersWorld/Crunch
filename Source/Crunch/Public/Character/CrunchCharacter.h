// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CrunchCharacter.generated.h"

UCLASS()
class CRUNCH_API ACrunchCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACrunchCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
