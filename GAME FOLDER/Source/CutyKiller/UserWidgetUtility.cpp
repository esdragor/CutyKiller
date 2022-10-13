// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetUtility.h"
#include "Math/UnrealMathUtility.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GameInstanceUtility.h"


FString UUserWidgetUtility::GenerateCodeParty()
{
	FString AllKeys = "AZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
	FString NewCode = "";

	for (int i = 0; i < 6; i++)
	{
		NewCode.InsertAt(i, AllKeys[FMath::RandRange(0, AllKeys.Len() - 1)]);
	}
	return NewCode;
}

void UUserWidgetUtility::CopyValueToClip(FString quote)
{
	FGenericPlatformMisc::ClipboardCopy(quote.GetCharArray().GetData());
}

void UUserWidgetUtility::LaunchAndSaveValueFromLobby(FText NbKiller, float SpeedCycleDayNight)
{
	UGameInstanceUtility* instance = Cast<UGameInstanceUtility>(GetGameInstance());

	instance->SpeedCycleDayNight = SpeedCycleDayNight;
	instance->NbKIllersToCreate = FCString::Atoi(*NbKiller.ToString());
}

bool UUserWidgetUtility::ValidNbOfKiller(int NbPlayers, FText NbKiller)
{
	int nb = FCString::Atoi(*NbKiller.ToString());
	return !(((NbPlayers <= nb || nb <= 0) && NbPlayers > 1) || (( nb > 1 || nb < 0) && NbPlayers == 1));
}

FString UUserWidgetUtility::ShowQuestDescription(FString description, int NbCurr, int NecessaryNb)
{
	if (NecessaryNb > 0)
	{
		return(description + " " + FString::FromInt(NbCurr) + "/" + FString::FromInt(NecessaryNb));
	}
	return description;
}
