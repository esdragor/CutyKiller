// Fill out your copyright notice in the Description page of Project Settings.


#include "RebinderWidget.h"



void URebinderWidget::InitInputList()
{
	MyInputSettings = UInputSettings::GetInputSettings();
}

FInputActionKeyMapping URebinderWidget::RecupInput(FName name)
{
	TArray <FInputActionKeyMapping> OutMappings;

	MyInputSettings->GetActionMappingByName(name, OutMappings);
	if (OutMappings.Num() == 0) return FInputActionKeyMapping();
	return OutMappings[0];
}

void URebinderWidget::ChangeInput(FName name, FInputChord chord)
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
