// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TestCharacterStatComponent.h"
#include "TestPlayerState.h"

void UTestHUDWidget::BindCharacterStat(UTestCharacterStatComponent* CharacterStat)
{
	TCHECK(CharacterStat != nullptr);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UTestHUDWidget::UpdateCharacterStat);
}
void UTestHUDWidget::BindPlayerState(ATestPlayerState * PlayerState)
{
	TCHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UTestHUDWidget::UpdatePlayerState);
}

void UTestHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	TCHECK(HPBar != nullptr);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	TCHECK(ExpBar != nullptr);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	TCHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	TCHECK(PlayerLevel != nullptr);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	TCHECK(CurrentScore != nullptr);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	TCHECK(HighScore != nullptr);
}

void UTestHUDWidget::UpdateCharacterStat()
{
	TCHECK(CurrentCharacterStat.IsValid());
	TLOG(Warning, TEXT("HP Changed"));
	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UTestHUDWidget::UpdatePlayerState()
{
	//TODO
	PlayerName->SetText(FText::FromString(TEXT("Chocobe")));
}
