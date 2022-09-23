// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateUtility.generated.h"

/**
 * 
 */
UCLASS()
class CUTYKILLER_API AGameStateUtility : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Night = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Day = false;

	UFUNCTION(BlueprintCallable)
	bool CheckDayNight(AActor *light);

};
