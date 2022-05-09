// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyEnums.generated.h"

UENUM()
enum StatusObj
{
	Trap     UMETA(DisplayName = "Trap"),
	Weapon      UMETA(DisplayName = "Weapon"),
};

UENUM(BlueprintType)
enum ConditionOfDeath
{
	None     UMETA(DisplayName = "None"),
	Sword      UMETA(DisplayName = "Sword"),
	Hand      UMETA(DisplayName = "Hand"),
	Explosion      UMETA(DisplayName = "Explosion"),
};

UCLASS()
class CUTYKILLER_API UMyEnums : public UObject
{
	GENERATED_BODY()
	
};
