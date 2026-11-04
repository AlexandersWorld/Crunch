// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Gameplay/Abilities/AbilityGauge.h"

void UAbilityGauge::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}
