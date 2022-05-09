// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnums.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 *
 */

UCLASS()
class CUTYKILLER_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ConditionOfDeath> CondDeath = ConditionOfDeath::None;
};
