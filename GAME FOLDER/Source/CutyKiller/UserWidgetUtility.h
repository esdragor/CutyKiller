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
};
