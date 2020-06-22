// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerState.h"

ATestPlayerState::ATestPlayerState()
{
	GameScore = 0;
}
int32 ATestPlayerState::GetGameScore() const
{
	return GameScore;
}

void ATestPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("TEST"));
	GameScore = 0;
}
