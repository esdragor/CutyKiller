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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float TurnRateGamepad;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool Attacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AWeapon* WeaponTmp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AWeapon* WeaponEquipped;

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

	UFUNCTION(BlueprintCallable)
		void LaunchSnap();

	UFUNCTION(BlueprintCallable)
		void AssignRole(RolesOfPlayer _role);

	UFUNCTION(BlueprintCallable)
		bool IsRoleAssigned() { return roleofcharacter != RolesOfPlayer::RoleNotAssigned; };

	UFUNCTION(BlueprintCallable)
		FString GetRole();

	UFUNCTION(BlueprintCallable)
		void TakeAhit(float damage, TEnumAsByte<ObjAttack> reasonOfHit, AActor* attacker);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ObjAttack> CondDeath = ObjAttack::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isDead = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool cantMove = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool EnemyInFront = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HealthValue = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DefenseValue = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackValue = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Hit = false;

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

