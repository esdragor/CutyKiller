// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnums.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"



UCLASS()
class CUTYKILLER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		bool Equipped = false;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		bool TrapEnclenched = false;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		float AttackValue = 1.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<ObjAttack> status;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		bool InUse = false;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BPSnap();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BPDropWeapon(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
