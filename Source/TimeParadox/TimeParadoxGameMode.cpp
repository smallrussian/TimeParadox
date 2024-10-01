// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeParadoxGameMode.h"
#include "TimeParadoxCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATimeParadoxGameMode::ATimeParadoxGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
