// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacterWidget.h"
#include "TestCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UTestCharacterWidget::BindCharacterStat(UTestCharacterStatComponent* NewCharacterStat)
{
	TCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UTestCharacterWidget::UpdateHPWidget);
}

void UTestCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	TCHECK(HPProgressBar != nullptr);
	UpdateHPWidget();
}

void UTestCharacterWidget::UpdateHPWidget()
{
	TLOG(Warning, TEXT("UpdateHPWidget"));
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			TLOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
