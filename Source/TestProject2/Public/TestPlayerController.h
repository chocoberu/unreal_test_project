// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATestPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	void ChangeInputMode(bool bGameMode = true);
	void ShowResultUI();

	class UTestHUDWidget* GetHUDWidget() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// UI ฐüทร
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI) TSubclassOf<class UTestHUDWidget> HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI) TSubclassOf<class UTestGamePlayWidget> MenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI) TSubclassOf<class UTestGamePlayResultWidget> ResultWidgetClass;

private:
	UPROPERTY() class UTestHUDWidget* HUDWidget;

	UPROPERTY() class UTestGamePlayWidget* MenuWidget;
	UPROPERTY() class UTestGamePlayResultWidget* ResultWidget;
	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

	void OnGamePause();

};
