// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"
#include "TestHUDWidget.h"
#include "TestPlayerState.h"

ATestPlayerController::ATestPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTestHUDWidget>
		UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));

	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
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

UTestHUDWidget * ATestPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UTestHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	auto TestPlayerState = Cast<ATestPlayerState>(PlayerState);
	TCHECK(TestPlayerState != nullptr);
	HUDWidget->BindPlayerState(TestPlayerState);
	TestPlayerState->OnPlayerStateChanged.Broadcast();
}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
