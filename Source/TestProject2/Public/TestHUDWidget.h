// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Blueprint/UserWidget.h"
#include "TestHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UTestCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ATestPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class UTestCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ATestPlayerState> CurrentPlayerState;

	UPROPERTY() class UProgressBar* HPBar;
	UPROPERTY() class UProgressBar* ExpBar;
	UPROPERTY() class UTextBlock* PlayerName;
	UPROPERTY() class UTextBlock* PlayerLevel;
};
