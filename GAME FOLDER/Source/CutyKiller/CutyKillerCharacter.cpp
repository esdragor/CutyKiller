// Copyright Epic Games, Inc. All Rights Reserved.

#include "CutyKillerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "MyEnums.h"
#include "FunctionUtility.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ACutyKillerCharacter

ACutyKillerCharacter::ACutyKillerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetBoxExtent(FVector(50.f, 50.f, 90.f));
	OverlapBox->SetupAttachment(RootComponent, USpringArmComponent::SocketName);

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ACutyKillerCharacter::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ACutyKillerCharacter::OnOverlapEnd);


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACutyKillerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACutyKillerCharacter::Attack);
	PlayerInputComponent->BindAction("Drop", IE_Released, this, &ACutyKillerCharacter::Drop);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ACutyKillerCharacter::Interact);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACutyKillerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACutyKillerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ACutyKillerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ACutyKillerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACutyKillerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACutyKillerCharacter::TouchStopped);
}

void ACutyKillerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsLocallyControlled())
	{
		AWeapon* tmp;
		tmp = Cast<AWeapon>(OtherActor);
		if (tmp && !tmp->Equipped) // c'est une weapon
		{
			WeaponTmp = tmp;
			BPShowWidgetEquip(true);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlapped");

}

void ACutyKillerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsLocallyControlled())
	{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Finish Overlapped");
	WeaponTmp = nullptr;
	BPShowWidgetEquip(false);
	}
}

void ACutyKillerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACutyKillerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ACutyKillerCharacter::Attack()
{
	if (!cantMove && GetRoleParameters().typeOfRoles.GetValue() == Naughty)
	{
		if (WeaponEquipped && WeaponEquipped->status == ObjAttack::TrapExplosion) // trap in hand so enclench it
		{
			WeaponEquipped->TrapEnclenched = true;
			BPSetTrap();
		}
		else if (!WeaponEquipped) // HandPunch
		{
			//Attacking = true;
			//BPAttacking();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Coup de point Non gerer !!!!!");
		}
		else
		{
			Attacking = true;
			DelayCPPValue(0.2f, Attacking, false); // local
			BPAttacking();
		}
	}
}

void ACutyKillerCharacter::Drop()
{
	if (WeaponEquipped)
		AttackValue -= WeaponEquipped->AttackValue;
	BPDropItem();
	WeaponEquipped = nullptr;
}

void ACutyKillerCharacter::Interact()
{

	if (WeaponTmp)
	{
		if (WeaponEquipped)
		{
			BPDropItem();
		}
		WeaponEquipped = WeaponTmp;
		WeaponEquipped->Equipped = true;
		WeaponTmp = nullptr;
		AttackValue += WeaponEquipped->AttackValue;
		BPInteract();
	}
}



void ACutyKillerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACutyKillerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACutyKillerCharacter::LaunchSnap()
{
	WeaponEquipped->BPSnap();
}

void ACutyKillerCharacter::AssignRole(RolesOfPlayer _role)
{
	roleofcharacter = _role;
	BPPrintRolesOnScreen();
}

FInfoRole ACutyKillerCharacter::GetRoleParameters()
{
	FInfoRole Inforole;

	switch (roleofcharacter)
	{
	case RoleNotAssigned:
		Inforole.role = "Killer";
		Inforole.color = FColor::Red;
		Inforole.typeOfRoles = Naughty;
		break;
	case GoodGuy:
		Inforole.role = "Cuty Animal";
		Inforole.color = FColor::Green;
		Inforole.typeOfRoles = Good;
		break;
	case Killer:
		Inforole.role = "Killer";
		Inforole.color = FColor::Red;
		Inforole.typeOfRoles = Naughty;
		break;
	default:
		break;
	}
	return Inforole;
}

void ACutyKillerCharacter::TakeAhit(float damage, TEnumAsByte<ObjAttack> reasonOfHit, AActor* attacker)
{
	if (!Invulnerability)
	{
		FTimerHandle UnusedHandle;
		Invulnerability = true;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [&]()
			{
				Invulnerability = false;
			}, 1, false);

		if (damage > DefenseValue)
			HealthValue -= (damage - DefenseValue);
		else
			HealthValue -= 1;
		CondDeath = reasonOfHit;
		if (HealthValue <= 0)
		{
			HealthValue = 0;
			isDead = true;
			cantMove = true;
			BPDead();
		}
		else
		{
			if (FVector::DotProduct(attacker->GetActorLocation(), GetActorLocation()) >= 0.0f)
				EnemyInFront = true;
			else
				EnemyInFront = false;
			BPTakeHit();
		}
	}

}

void ACutyKillerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && !cantMove)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACutyKillerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && !cantMove)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ACutyKillerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}
