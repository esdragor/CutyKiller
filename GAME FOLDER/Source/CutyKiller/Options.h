// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "Framework/Commands/InputChord.h"
#include "MyEnums.h"
#include "Blueprint/UserWidget.h"
#include "Options.generated.h"


USTRUCT(BlueprintType)
struct FOptionsGraphics
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		FString ScreenMode = "Windowed";
	UPROPERTY(BlueprintReadOnly)
		int32 WindowResolutionX = 1920;
	UPROPERTY(BlueprintReadOnly)
		int32 WindowResolutionY = 1080;

};

UCLASS()
class CUTYKILLER_API UOptions : public UUserWidget
{
	GENERATED_BODY()

protected:
	UInputSettings* MyInputSettings;
	UGameUserSettings* MyGameUserSettings;
	UPROPERTY(BlueprintReadWrite)
		float timer = -1;
	UPROPERTY(BlueprintReadOnly)
	FOptionsGraphics saveData;

private:
	EWindowMode::Type prevMode;
	FIntPoint prevResolution;

protected:
	~UOptions();
	UFUNCTION(BlueprintCallable)
		void InitInputList();
	UFUNCTION(BlueprintCallable)
		FKey RecupActionInput(FName name);
	UFUNCTION(BlueprintCallable)
		FKey RecupAxisInput(FName name, bool IsSecondParameter);
	UFUNCTION(BlueprintCallable)
		void ChangeActionInput(FName name, FInputChord chord);
	UFUNCTION(BlueprintCallable)
		void ChangeAxisInput(FName name, FInputChord chord, bool IsSecondParameter);
	UFUNCTION(BlueprintCallable)
		void InitKeys(TArray<FOptionParameter> options);
	UFUNCTION(BlueprintImplementableEvent)
		void InitKey(FOptionParameter option);
	UFUNCTION(BlueprintCallable)
		void InitGraphicsSettings();
	UFUNCTION(BlueprintImplementableEvent)
		void InitGraphicsOptionUI();
	UFUNCTION(BlueprintCallable)
		void ChangeWindowedMode(FString mode);
	UFUNCTION(BlueprintCallable)
		void ChangeScreenResolution(FString mode);
	UFUNCTION(BlueprintCallable)
		void ApplySettings();
	UFUNCTION(BlueprintImplementableEvent)
		void ConfirmNewResolution();

private:
	void ChangeResOrWindows();
	void Save();
	void Load();
};
