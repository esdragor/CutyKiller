// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceUtility.generated.h"

/**
 *
 */
UCLASS()
class CUTYKILLER_API UGameInstanceUtility : public UGameInstance
{
	GENERATED_BODY()

public:
UPROPERTY(BlueprintReadWrite)
	FName NameOfPlayer = "None";

	UPROPERTY(BlueprintReadWrite)
	float SpeedCycleDayNight = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	FString LobbyCode = "";

	UPROPERTY(BlueprintReadWrite)
	int NbKIllersToCreate = 1;
};
