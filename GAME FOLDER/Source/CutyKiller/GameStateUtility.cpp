// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateUtility.h"

bool AGameStateUtility::CheckDayNight(AActor *light)
{
	if (!Night && light->GetActorTransform().GetRotation().Y > -0.1f)
	{
		Night = true;
		Day = false;
	}
	else if (!Day && light->GetActorTransform().GetRotation().Y < 0.1f)
	{
		Night = false;
		Day = true;
	}
	return true;
}
