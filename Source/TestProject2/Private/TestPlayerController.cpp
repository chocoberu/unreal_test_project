// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "TestHUDWidget.h"
#include "TestPlayerState.h"
#include "TestGamePlayWidget.h"
#include "TestGamePlayResultWidget.h"
#include "TestGameMode.h"
#include "TestItemGenerator.h"

ATestPlayerController::ATestPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTestHUDWidget>
		UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));

	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UTestGamePlayWidget>
		UI_MENU_C(TEXT("/Game/UI/UI_Menu.UI_Menu_C"));

	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}
	static ConstructorHelpers::FClassFinder<UTestGamePlayResultWidget>
		UI_RESULT_C(TEXT("/Game/UI/UI_Result.UI_Result_C"));

	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
	}

}
void ATestPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATestPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
}

void ATestPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}
void ATestPlayerController::ShowResultUI()
{
	auto TestGameMode = Cast<ATestGameMode>(UGameplayStatics::GetGameMode(this));
	TCHECK(TestGameMode != nullptr);
	ResultWidget->AddToViewport();
	ChangeInputMode(false);

	UWorld* CurrentWorld = GetWorld();
	for (TObjectIterator<ATestItemGenerator> Iter; Iter; ++Iter)
	{
		(*Iter)->ClearTimerHandle();
	}
}
UTestHUDWidget * ATestPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UTestHUDWidget>(this, HUDWidgetClass);
	TCHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<UTestGamePlayResultWidget>(this, ResultWidgetClass);
	TCHECK(ResultWidget != nullptr);

	auto TestPlayerState = Cast<ATestPlayerState>(PlayerState);
	TCHECK(TestPlayerState != nullptr);
	HUDWidget->BindPlayerState(TestPlayerState);
	TestPlayerState->OnPlayerStateChanged.Broadcast();


}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ATestPlayerController::OnGamePause);
}
void ATestPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UTestGamePlayWidget>(this, MenuWidgetClass);
	TCHECK(MenuWidget != nullptr);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);

}