// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/PlayerState.h"
#include "TestPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);
/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATestPlayerState();
	int32 GetGameScore() const;
	
	void InitPlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient) int32 GameScore;
};
