// Fill out your copyright notice in the Description page of Project Settings.

#include "Options.h"
#include "Kismet/KismetStringLibrary.h"
#include "JsonObjectConverter.h"

UOptions::~UOptions()
{
	Save();
}

void UOptions::InitInputList()
{
	MyInputSettings = UInputSettings::GetInputSettings();
}

FKey UOptions::RecupActionInput(FName name)
{
	TArray <FInputActionKeyMapping> OutMappings;

	MyInputSettings->GetActionMappingByName(name, OutMappings);
	if (OutMappings.Num() == 0) return FKey();
	return OutMappings[0].Key;
}

FKey UOptions::RecupAxisInput(FName name, bool IsSecondParameter)
{
	TArray<FInputAxisKeyMapping> OutMappings;
	MyInputSettings->GetAxisMappingByName(name, OutMappings);

	// Assign each key to the correct direction
	for (FInputAxisKeyMapping Keys : OutMappings)
	{
		if (Keys.Scale == 1.0f && !IsSecondParameter)
			return Keys.Key;
		else if (Keys.Scale == -1.0f && IsSecondParameter)
			return Keys.Key;
	}
	return FKey();
}

void UOptions::ChangeActionInput(FName name, FInputChord chord)
{
	FInputActionKeyMapping MyActionMapping;
	TArray <FInputActionKeyMapping> OutMappings;

	MyInputSettings->GetActionMappingByName(name, OutMappings);
	if (OutMappings.Num() == 0) return;
	MyActionMapping = OutMappings[0];
	MyInputSettings->RemoveActionMapping(MyActionMapping);
	MyActionMapping.Key = chord.Key;

	MyInputSettings->AddActionMapping(MyActionMapping);
	MyInputSettings->SaveConfig();
}

void UOptions::ChangeAxisInput(FName name, FInputChord chord, bool IsSecondParameter)
{
	TArray<FInputAxisKeyMapping> OutMappings;

	MyInputSettings->GetAxisMappingByName(name, OutMappings);

	if (OutMappings.Num() == 0) return;

	// Assign each key to the correct direction
	for (FInputAxisKeyMapping Keys : OutMappings)
	{
		if ((Keys.Scale == 1.0f && !IsSecondParameter)
			|| (Keys.Scale == -1.0f && IsSecondParameter))
		{
			MyInputSettings->RemoveAxisMapping(Keys);
			Keys.Key = chord.Key;
			MyInputSettings->AddAxisMapping(Keys);
		}
	}
	MyInputSettings->SaveConfig();
}

void UOptions::InitKeys(TArray<FOptionParameter> options)
{
	for (size_t i = 0; i < options.Num(); i++)
	{
		InitKey(options[i]);
	}
}

void UOptions::InitGraphicsSettings()
{
	MyGameUserSettings = GEngine->GameUserSettings;

	if (FPaths::FileExists(FPaths::ProjectContentDir() + TEXT("/Save.json")))
	{
		Load();
	}
	else
	{
		Save();
	}

	InitGraphicsOptionUI();
}

void UOptions::ChangeWindowedMode(FString mode, bool needConfirmation)
{
	prevMode = MyGameUserSettings->GetFullscreenMode();

	if (mode == "Fullscreen")
		MyGameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	else if (mode == "Windowed Fullscreen")
		MyGameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	else
		MyGameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	saveData.ResWinOptions.ScreenMode = mode;
	ChangeResOrWindows(needConfirmation);
}

void UOptions::ChangeWindowedMode(EWindowMode::Type mode, bool needConfirmation)
{
	prevMode = MyGameUserSettings->GetFullscreenMode();

	MyGameUserSettings->SetFullscreenMode(mode);
	ChangeResOrWindows(needConfirmation);
}

void UOptions::ChangeScreenResolution(FString Resolution, bool needConfirmation)
{
	FIntPoint newRes;

	int32 indexX = Resolution.Find(TEXT("x"), ESearchCase::IgnoreCase, ESearchDir::Type::FromStart, 0);

	newRes.X = UKismetStringLibrary::Conv_StringToInt(Resolution.Mid(0, indexX - 1));
	newRes.Y = UKismetStringLibrary::Conv_StringToInt(Resolution.Mid(indexX + 1, Resolution.Len() - indexX));

	prevResolution = MyGameUserSettings->GetScreenResolution();

	saveData.ResWinOptions.WindowResolutionX = newRes.X;
	saveData.ResWinOptions.WindowResolutionY = newRes.Y;
	MyGameUserSettings->SetScreenResolution(newRes);
	ChangeResOrWindows(needConfirmation);
}

void UOptions::ChangeScreenResolution(FIntPoint newRes, bool needConfirmation)
{
	prevResolution = MyGameUserSettings->GetScreenResolution();

	saveData.ResWinOptions.WindowResolutionX = newRes.X;
	saveData.ResWinOptions.WindowResolutionY = newRes.Y;
	MyGameUserSettings->SetScreenResolution(newRes);
	ChangeResOrWindows(needConfirmation);
}

void UOptions::ApplySettings()
{
	while (stackVectorGraph.size() > 0)
	{
		(this->*stackVectorGraph.back())();
		stackVectorGraph.pop_back();
	}

	MyGameUserSettings->ValidateSettings();
	MyGameUserSettings->ApplySettings(false);
	//Save();
}

void UOptions::ResetToPreviousWinModeResSettings()
{

	ChangeWindowedMode(prevMode, false);
	ChangeScreenResolution(prevResolution, false);
	timer = -1;
}

void UOptions::ResetGraphicsSettings()
{
	// ADD HERE le reset de toutes le valeurs graphics de base
}

void UOptions::AddVerticalSyncToApply(bool Vsync)
{
	saveData.GraphicsSettings.VSync = Vsync;
	stackVectorGraph.push_back(&UOptions::SetVSync);
}

void UOptions::AddViewDistanceToApply(int32 viewDistance)
{
	saveData.GraphicsSettings.viewDistance = viewDistance;
	stackVectorGraph.push_back(&UOptions::SetViewDistance);
}


void UOptions::ChangeResOrWindows(bool needConfirmation)
{
	MyGameUserSettings->ApplyResolutionSettings(false);
	if (!needConfirmation || bypass) return;
	ConfirmNewResolution();
	timer = 10;
}

void UOptions::Save()
{
	FString buffer;


	FJsonObjectConverter::UStructToJsonObjectString(saveData.ResWinOptions, buffer);
	FFileHelper::SaveStringToFile(*buffer, *(FPaths::ProjectContentDir() + TEXT("/Save.json")));
}

void UOptions::Load()
{
	FString buffer;

	FFileHelper::LoadFileToString(buffer, *(FPaths::ProjectContentDir() + TEXT("/Save.json")));

	FResWindowStruct JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FResWindowStruct>(
		buffer,
		&JsonData,
		0, 0);

	saveData.ResWinOptions.ScreenMode = JsonData.ScreenMode;
	saveData.ResWinOptions.WindowResolutionX = JsonData.WindowResolutionX;
	saveData.ResWinOptions.WindowResolutionY = JsonData.WindowResolutionY;

	ChangeWindowedMode(saveData.ResWinOptions.ScreenMode, false);
	FString Resolution = "";
	Resolution.AppendInt(saveData.ResWinOptions.WindowResolutionX);
	Resolution.Append(" x ");
	Resolution.AppendInt(saveData.ResWinOptions.WindowResolutionY);
	ChangeScreenResolution(Resolution, false);

	MyGameUserSettings->LoadSettings();
	saveData.GraphicsSettings.VSync = MyGameUserSettings->bUseVSync;
	saveData.GraphicsSettings.viewDistance = MyGameUserSettings->GetViewDistanceQuality();

}

void UOptions::SetVSync()
{
	MyGameUserSettings->bUseVSync = saveData.GraphicsSettings.VSync;
}

void UOptions::SetViewDistance()
{
	MyGameUserSettings->SetViewDistanceQuality(saveData.GraphicsSettings.viewDistance);
}
