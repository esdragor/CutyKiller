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
		void BPShowWidgetEquip(bool showed);

	UFUNCTION(BlueprintImplementableEvent)
		void BPDropItem();

	UFUNCTION(BlueprintImplementableEvent)
		void BPSetTrap();

	UFUNCTION(BlueprintImplementableEvent)
		void BPAttacking();

	UFUNCTION(BlueprintImplementableEvent)
		void BPInteract();

	UFUNCTION(BlueprintImplementableEvent)
		void BPDead();

	UFUNCTION(BlueprintImplementableEvent)
		void BPTakeHit();

	UFUNCTION(BlueprintImplementableEvent)
		void BPPrintRolesOnScreen();

	UFUNCTION(BlueprintCallable)
		void LaunchSnap();

	UFUNCTION(BlueprintCallable)
		void AssignRole(RolesOfPlayer _role);

	UFUNCTION(BlueprintCallable)
		bool IsRoleAssigned() { return roleofcharacter != RolesOfPlayer::RoleNotAssigned; };

	UFUNCTION(BlueprintCallable)
		FInfoRole GetRoleParameters();

	UFUNCTION(BlueprintCallable)
		void TakeAhit(float damage, TEnumAsByte<ObjAttack> reasonOfHit, AActor* attacker);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ObjAttack> CondDeath = ObjAttack::None;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		bool isDead = false;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		bool cantMove = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnemyInFront = false;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float HealthValue = 100;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float DefenseValue = 0;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		float AttackValue = 40.f;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
		bool Hit = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float TurnRateGamepad;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
		bool Attacking = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		AWeapon* WeaponTmp;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		AWeapon* WeaponEquipped;

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
	float CalcDamage(ObjAttack reasonOfHit);

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

