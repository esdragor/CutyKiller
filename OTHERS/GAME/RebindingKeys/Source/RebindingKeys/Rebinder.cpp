// Fill out your copyright notice in the Description page of Project Settings.


#include "Rebinder.h"
#include "GameFramework/InputSettings.h"

// Sets default values
ARebinder::ARebinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARebinder::BeginPlay()
{
	Super::BeginPlay();

	UInputSettings* MyInputSettings = UInputSettings::GetInputSettings();
	FInputActionKeyMapping MyActionMapping;
	TArray <FInputActionKeyMapping> OutMappings;

	MyInputSettings->GetActionMappingByName("Jump", OutMappings);
	if (OutMappings.Num() == 0) return;
	MyActionMapping = OutMappings[0];
	MyInputSettings->RemoveActionMapping(MyActionMapping);
	MyActionMapping.Key = EKeys::S;

	MyInputSettings->AddActionMapping(MyActionMapping);
	MyInputSettings->SaveConfig();
	
}

// Called every frame
void ARebinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

