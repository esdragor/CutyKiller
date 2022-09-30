// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#define DelayCPPValue(delay, valueToChange, NewValue) 	FTimerHandle UnusedHandle; GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [&]() { ((valueToChange) = (NewValue)); }, delay, false);
#define DelayCPPFunction(delay, funcptr) 	FTimerHandle UnusedHandle; 	caller->GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [&]() {funcptr();}, delay, false);
#define PrintMessage(delay, color, msg) 	GEngine->AddOnScreenDebugMessage(-1, delay, color, msg);
/**
 * 
 */
class CUTYKILLER_API FunctionUtility
{
public:
	FunctionUtility();
	~FunctionUtility();
};
