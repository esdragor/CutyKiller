// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyEnums.generated.h"

UENUM(BlueprintType)
enum ObjAttack
{
	None     UMETA(DisplayName = "None"),
	Sword      UMETA(DisplayName = "Sword"),
	Hand      UMETA(DisplayName = "Hand"),
	TrapExplosion      UMETA(DisplayName = "TrapExplosion"),
};

UCLASS()
class CUTYKILLER_API UMyEnums : public UObject
{
	GENERATED_BODY()
	
};
