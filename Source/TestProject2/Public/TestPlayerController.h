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

	class UTestHUDWidget* GetHUDWidget() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI) TSubclassOf<class UTestHUDWidget> HUDWidgetClass;

private:
	UPROPERTY() class UTestHUDWidget* HUDWidget;

};
