// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/InputSettings.h"
#include "Framework/Commands/InputChord.h"
#include "Blueprint/UserWidget.h"
#include "RebinderWidget.generated.h"

/**
 *
 */
UCLASS()
class REBINDINGKEYS_API URebinderWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UInputSettings* MyInputSettings;

protected:
	UFUNCTION(BlueprintCallable)
		void InitInputList();
	UFUNCTION(BlueprintCallable)
		FInputActionKeyMapping RecupInput(FName name);
	UFUNCTION(BlueprintCallable)
		void ChangeInput(FName name, FInputChord chord);

};
