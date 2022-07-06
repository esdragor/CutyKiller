// Copyright Epic Games, Inc. All Rights Reserved.

#include "CutyKillerGameMode.h"
#include "CutyKillerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACutyKillerGameMode::ACutyKillerGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
