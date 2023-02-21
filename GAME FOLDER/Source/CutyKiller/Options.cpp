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

void UOptions::ChangeWindowedMode(FString mode)
{
	prevMode = MyGameUserSettings->GetFullscreenMode();

	if (mode == "Fullscreen")
		MyGameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	else if (mode == "Windowed Fullscreen")
		MyGameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	else
		MyGameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	saveData.ResWinOptions.ScreenMode = mode;
	ChangeResOrWindows();
}

void UOptions::ChangeScreenResolution(FString Resolution)
{
	FIntPoint newRes;

	int32 indexX = Resolution.Find(TEXT("x"), ESearchCase::IgnoreCase, ESearchDir::Type::FromStart, 0);

	newRes.X = UKismetStringLibrary::Conv_StringToInt(Resolution.Mid(0, indexX - 1));
	newRes.Y = UKismetStringLibrary::Conv_StringToInt(Resolution.Mid(indexX + 1, Resolution.Len() - indexX));

	prevResolution = MyGameUserSettings->GetScreenResolution();

	saveData.ResWinOptions.WindowResolutionX = newRes.X;
	saveData.ResWinOptions.WindowResolutionY = newRes.Y;
	MyGameUserSettings->SetScreenResolution(newRes);
	ChangeResOrWindows();
}

void UOptions::ApplySettings()
{
	//saveData.prevMode = prevMode;
	//saveData.prevResolution = prevResolution;

	Save();
}

void UOptions::ChangeResOrWindows()
{
	MyGameUserSettings->ApplyResolutionSettings(false);
	ConfirmNewResolution();
	timer = 10;
}

void UOptions::Save()
{
	FString buffer;


	FJsonObjectConverter::UStructToJsonObjectString(saveData, buffer);
	FFileHelper::SaveStringToFile(*buffer, *(FPaths::ProjectContentDir() + TEXT("/Save.json")));
}

void UOptions::Load()
{
	FString buffer;

	FFileHelper::LoadFileToString(buffer, *(FPaths::ProjectContentDir() + TEXT("/Save.json")));
	



	FOptionsGraphics JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FOptionsGraphics>(
		buffer,
		&JsonData,
		0, 0);



	return;
	//TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(buffer);
	//TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	//if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	//{
	//		FResWindowStruct ResWinOptions = JsonObject->GetArrayField("")
	//		FGraphicsSetings GraphicsSetings;

	//		ResWinOptions.ScreenMode = JsonObject->GetStringField(TEXT("ScreenMode"));
	//		ResWinOptions.WindowResolutionX = JsonObject->GetIntegerField(TEXT("windowResolutionX"));
	//		ResWinOptions.WindowResolutionY = JsonObject->GetIntegerField(TEXT("windowResolutionY"));
	//}

	ChangeWindowedMode(saveData.ResWinOptions.ScreenMode);
	FString Resolution = "";
	Resolution.AppendInt(saveData.ResWinOptions.WindowResolutionX);
	Resolution.Append(" x ");
	Resolution.AppendInt(saveData.ResWinOptions.WindowResolutionY);
	ChangeScreenResolution(Resolution);
}
