// Copyright Epic Games, Inc. All Rights Reserved.

#include "GraveyardGameMode.h"
#include "GraveyardCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGraveyardGameMode::AGraveyardGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
