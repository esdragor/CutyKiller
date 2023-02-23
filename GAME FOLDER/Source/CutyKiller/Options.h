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
struct FResWindowStruct
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

USTRUCT(BlueprintType)
struct FGraphicsSetings
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		bool VSync = false;
	UPROPERTY(BlueprintReadOnly)
		int32 viewDistance = false;
};

USTRUCT(BlueprintType)
struct FOptionsGraphics
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		FResWindowStruct ResWinOptions;
	UPROPERTY(BlueprintReadOnly)
		FGraphicsSetings GraphicsSettings;

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
	UPROPERTY(BlueprintReadWrite)
		bool bypass = true;
	UPROPERTY(BlueprintReadOnly)
	FOptionsGraphics saveData;

private:
	EWindowMode::Type prevMode;
	FIntPoint prevResolution;

	std::vector<void (UOptions::*) ()> stackVectorGraph;



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
		void ChangeWindowedMode(FString mode, bool needConfirmation);
	UFUNCTION(BlueprintCallable)
		void ChangeScreenResolution(FString mode, bool needConfirmation);
	UFUNCTION(BlueprintCallable)
		void ApplySettings();
	UFUNCTION(BlueprintCallable)
		void ResetToPreviousWinModeResSettings();
	UFUNCTION(BlueprintCallable)
		void ResetGraphicsSettings();
	UFUNCTION(BlueprintCallable)
		void AddVerticalSyncToApply(bool Vsync);
	UFUNCTION(BlueprintCallable)
		void AddViewDistanceToApply(int32 viewDistance);
	UFUNCTION(BlueprintImplementableEvent)
		void ConfirmNewResolution();

	void ChangeWindowedMode(EWindowMode::Type mode, bool needConfirmation);
	void ChangeScreenResolution(FIntPoint newRes, bool needConfirmation);

	void SetVSync();
	void SetViewDistance();


private:
	void ChangeResOrWindows(bool needConfirmation);
	void Save();
	void Load();
};
