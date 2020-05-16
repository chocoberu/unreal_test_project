// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TestProject2GameMode.h"
#include "TestProject2Character.h"
#include "UObject/ConstructorHelpers.h"

ATestProject2GameMode::ATestProject2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
