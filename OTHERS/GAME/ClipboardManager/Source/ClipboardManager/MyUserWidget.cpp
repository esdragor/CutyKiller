// Fill out your copyright notice in the Description page of Project Settings.

#include "HoloLens/HoloLensPlatformApplicationMisc.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include "MyUserWidget.h"


//void Test(FString quote)
//{
//	//FHoloLensPlatformApplicationMisc::ClipboardCopy(quote.GetCharArray().GetData());
//}

void UMyUserWidget::CopyValueToClip(FString quote)
{
	FGenericPlatformMisc::ClipboardCopy(quote.GetCharArray().GetData());
}
