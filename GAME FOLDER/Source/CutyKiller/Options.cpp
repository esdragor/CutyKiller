// Fill out your copyright notice in the Description page of Project Settings.


#include "Options.h"

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
