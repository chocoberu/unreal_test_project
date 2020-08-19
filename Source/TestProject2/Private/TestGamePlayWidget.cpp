// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGamePlayWidget.h"
#include "Components/Button.h"
#include "TestPlayerController.h"

void UTestGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (ResumeButton != nullptr)
		ResumeButton->OnClicked.AddDynamic(this, &UTestGamePlayWidget::OnResumeClicked);

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (RetryGameButton != nullptr)
		RetryGameButton->OnClicked.AddDynamic(this, &UTestGamePlayWidget::OnRetryGameClicked);
}

void UTestGamePlayWidget::OnResumeClicked()
{
	auto TestPlayerController = Cast<ATestPlayerController>(GetOwningPlayer());
	TCHECK(TestPlayerController != nullptr);

	RemoveFromParent(); // 뷰포트에 띄워진 자신을 제거 가능
	TestPlayerController->ChangeInputMode(true);
	TestPlayerController->SetPause(false);
}

void UTestGamePlayWidget::OnRetryGameClicked()
{
	auto TestPlayerController = Cast<ATestPlayerController>(GetOwningPlayer());
	TCHECK(TestPlayerController != nullptr);
	TestPlayerController->RestartLevel();
}
