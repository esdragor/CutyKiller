// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetUtility.h"
#include "Math/UnrealMathUtility.h"

FString UUserWidgetUtility::GenerateCodeParty()
{
	FString AllKeys = "AZERTYUIOPQSDFGHJKLMWXCVBN1234567890";
	FString NewCode = "";

	for (int i = 0; i < 6; i++)
	{
		NewCode.InsertAt(i, AllKeys[FMath::RandRange(0, AllKeys.Len() - 1)]);
	}
	return NewCode;
}
