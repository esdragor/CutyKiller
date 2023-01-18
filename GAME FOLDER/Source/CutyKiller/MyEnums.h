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


UENUM(BlueprintType)
enum RolesOfPlayer
{
	RoleNotAssigned     UMETA(DisplayName = "RoleNotAssigned"),
	GoodGuy      UMETA(DisplayName = "GoodGuy"),
	Killer      UMETA(DisplayName = "Killer"),
};

UENUM(BlueprintType)
enum AnimalOfPlayer
{
	AnimalNotAssigned     UMETA(DisplayName = "AnimalNotAssigned"),
	Dog      UMETA(DisplayName = "Dog"),
	Cat      UMETA(DisplayName = "Cat"),
	Reindeer      UMETA(DisplayName = "Reindeer"),
};

UENUM(BlueprintType)
enum RolesFunction
{
	FunctionNotAssigned     UMETA(DisplayName = "FunctionNotAssigned"),
	Good      UMETA(DisplayName = "Good"),
	Naughty      UMETA(DisplayName = "Naughty"),
};

USTRUCT(BlueprintType)
struct FOptionParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FName name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool isAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		bool IsSecondParameter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FName print;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FKey defaultKey;
};

USTRUCT(BlueprintType)
struct FInfoRole
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role of player")
		FString role;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color of role")
		FColor color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type Of Roles")
		TEnumAsByte<RolesFunction> typeOfRoles;
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ID of Quest")
		int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "description of Quest")
		FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nb finish by player")
		int CurrentNb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nb necessary to complete quest")
		int NecessaryNb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "delay to complete quest")
		float Delay;
};

UCLASS()
class CUTYKILLER_API UMyEnums : public UObject
{
	GENERATED_BODY()

};
