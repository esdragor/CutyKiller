// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rebinder.generated.h"

UCLASS()
class REBINDINGKEYS_API ARebinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARebinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
