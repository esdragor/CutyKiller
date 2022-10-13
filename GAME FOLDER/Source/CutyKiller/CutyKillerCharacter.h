// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <CutyKiller/Weapon.h>
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "CutyKillerCharacter.generated.h"

UCLASS(config = Game)
class ACutyKillerCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* OverlapBox;
public:
	ACutyKillerCharacter();

	UFUNCTION(BlueprintImplementableEvent)
		void BPShowEquippedWidget(bool IsShow);

	UFUNCTION(BlueprintImplementableEvent)
		void BPDropItem();

	UFUNCTION(BlueprintImplementableEvent)
		void BPSetTrap();

	UFUNCTION(BlueprintImplementableEvent)
		void BPAttacking();

	UFUNCTION(BlueprintImplementableEvent)
		void BPInteract();

	UFUNCTION(BlueprintImplementableEvent)
		void BPPower();

	UFUNCTION(BlueprintImplementableEvent)
		void BPPower2();

	UFUNCTION(BlueprintImplementableEvent)
		void BPDead();

	UFUNCTION(BlueprintImplementableEvent)
		void BPTakeHit();

	UFUNCTION(BlueprintImplementableEvent)
		void BPUpdateQuest();

	UFUNCTION(BlueprintImplementableEvent)
		void BPShowProgressQuest();

	UFUNCTION(BlueprintImplementableEvent)
		void BPPrintRolesOnScreen();

	UFUNCTION(BlueprintImplementableEvent)
		void SwitchDayNight(bool IsNight);

	UFUNCTION(BlueprintCallable)
		void LaunchSnap();

	UFUNCTION(BlueprintCallable)
		void AssignRole(RolesOfPlayer _role);
	UFUNCTION(BlueprintCallable)
		void AssignAnimal();

	UFUNCTION(BlueprintCallable)
		void SetWeaponEquip(AWeapon* weap);

	UFUNCTION(BlueprintCallable)
		void SetDeathStatus(bool _cantMove, bool _ISdead);

	UFUNCTION(BlueprintCallable)
		bool IsRoleAssigned() { return roleofcharacter != RolesOfPlayer::RoleNotAssigned; };

	UFUNCTION(BlueprintCallable)
		FInfoRole GetRoleParameters();

	UFUNCTION(BlueprintCallable)
		void TakeAhit(float damage, TEnumAsByte<ObjAttack> reasonOfHit, AActor* attacker);

	UFUNCTION(BlueprintCallable)
		void InitCamPostProcess(FPostProcessSettings good, FPostProcessSettings evil);

	UFUNCTION(BlueprintCallable)
		void SwitchLights(ULightComponent* OnEnable, ULightComponent* OnDisable);

	UFUNCTION(BlueprintCallable)
		AActor* FindClosestPlayer(TArray<AActor*>  players);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ObjAttack> CondDeath = ObjAttack::None;

	UPROPERTY(Replicated, BlueprintReadWrite)
		bool isDead = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
		bool cantMove = true;

	UPROPERTY(BlueprintReadWrite)
		bool EnemyInFront = false;

	UPROPERTY(BlueprintReadWrite)
		float TriggeredDuration = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		int TriggeredID = -1;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float HealthValue = 100;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float DefenseValue = 0;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float AttackValue = 40.f;

	UPROPERTY(Replicated, BlueprintReadWrite)
		bool Hit = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float TurnRateGamepad;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
		bool Attacking = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		AWeapon* WeaponTmp;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		AWeapon* WeaponEquipped;

	UPROPERTY(EditAnywhere)
		TEnumAsByte <AnimalOfPlayer> animal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FQuest> MyQuests;

	float CooldownUtilisationPower = 0.1f;

	bool CanUsePower = false;

	float CooldownUtilisationPower2 = 0.1f;

	bool CanUsePower2 = false;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);


	RolesOfPlayer roleofcharacter = RolesOfPlayer::RoleNotAssigned;

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Attack();
	void Drop();
	void Interact();
	void Power();
	void Power2();
	float CalcDamage(ObjAttack reasonOfHit);
	void UpdateQuest(int index);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	  // declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool Invulnerability = false;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

