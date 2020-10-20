// Copyright Epic Games, Inc. All Rights Reserved.

#include "VirtualAcresGameMode.h"
#include "VirtualAcresCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVirtualAcresGameMode::AVirtualAcresGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_Blueprints/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
