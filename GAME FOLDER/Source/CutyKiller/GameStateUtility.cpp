// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateUtility.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CutyKillerCharacter.h"
#include "FunctionUtility.h"

void AGameStateUtility::CheckDayNight(AActor* light)
{
	if (light->GetActorTransform().GetRotation().Y > 0.01f)
	{
		SecondDay = true;
	}
	else if (light->GetActorTransform().GetRotation().Y < -0.01f && Day && SecondDay)
	{
		Night = true;
		Day = false;
		SecondDay = false;

		TArray< AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACutyKillerCharacter::StaticClass(), OutActors);
		for (int i = 0; i < OutActors.Num(); i++)
		{
			Cast<ACutyKillerCharacter>(OutActors[i])->SwitchDayNight(Night);
		}
	}
	else if (Night && light->GetActorTransform().GetRotation().Y < -0.9999f)
	{
		Night = false;
		Day = true;

		TArray< AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACutyKillerCharacter::StaticClass(), OutActors);
		for (int i = 0; i < OutActors.Num(); i++)
		{
			Cast<ACutyKillerCharacter>(OutActors[i])->SwitchDayNight(Night);
		}
	}
}
