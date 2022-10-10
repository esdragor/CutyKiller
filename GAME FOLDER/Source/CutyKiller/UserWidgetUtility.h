// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetUtility.generated.h"

/**
 * 
 */
UCLASS()
class CUTYKILLER_API UUserWidgetUtility : public UUserWidget
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable)
		FString GenerateCodeParty();

		UFUNCTION(BlueprintCallable)
			void CopyValueToClip(FString quote);

		UFUNCTION(BlueprintCallable)
			void LaunchAndSaveValueFromLobby(FText NbKiller, float SpeedCycleDayNight);

		UFUNCTION(BlueprintCallable)
			bool ValidNbOfKiller(int NbPlayers, FText NbKiller);

		UFUNCTION(BlueprintCallable)
			FString ShowQuestDescription(FString description, int NbCurr, int NecessaryNb);
};
