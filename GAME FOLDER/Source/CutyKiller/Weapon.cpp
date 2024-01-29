// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Core.h"
#include <Net/UnrealNetwork.h>

#include "CutyKillerCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetBoxExtent(FVector(100.f, 35.f, 24.f));
	OverlapBox->SetupAttachment(RootComponent);

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);
	OverlapBox->SetCollisionProfileName("OverlapAll");
	OverlapBox->SetCollisionObjectType(ECC_GameTraceChannel1);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	status = None;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, Equipped);
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACutyKillerCharacter* tmp;
	tmp = Cast<ACutyKillerCharacter>(OtherActor);
	if (!tmp) return;
	if (tmp && !Equipped)
	{
		tmp->WeaponTmp = this;
		tmp->BPShowEquippedWidget(true);
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex)
{
	ACutyKillerCharacter* tmp;
	tmp = Cast<ACutyKillerCharacter>(OtherActor);
	if (!tmp) return;
	if (tmp && Equipped)
	{
		tmp->WeaponTmp = nullptr;
		tmp->BPShowEquippedWidget(false);
	}
}
