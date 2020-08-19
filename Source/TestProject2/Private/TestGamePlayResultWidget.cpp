// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGamePlayResultWidget.h"
#include "TestGameMode.h"
#include "TestGameInstance.h"
#include "Components/TextBlock.h"

void UTestGamePlayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	TCHECK(Result != nullptr);
	auto TestGameInstance = Cast<UTestGameInstance>(GetWorld()->GetGameInstance());
	Result->SetText(FText::FromString(TestGameInstance->GetIsClear() ? TEXT("Game Clear") : TEXT("Game Over")));

	TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	TCHECK(TotalScore != nullptr);

}
