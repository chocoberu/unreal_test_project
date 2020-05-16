// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"
#include "TestCharacter1.h"
#include "TestPlayerController.h"

ATestGameMode::ATestGameMode()
{
	DefaultPawnClass = ATestCharacter1::StaticClass();
	PlayerControllerClass = ATestPlayerController::StaticClass();
}

void ATestGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
