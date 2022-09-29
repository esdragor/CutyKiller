// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */

#define WIN32_LEAN_AND_MEAN


UCLASS()
class CLIPBOARDMANAGER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void CopyValueToClip(FString quote);
	
};
