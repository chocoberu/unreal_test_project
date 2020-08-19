// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Blueprint/UserWidget.h"
#include "TestGamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnResumeClicked();
	UFUNCTION()
		void OnRetryGameClicked();

	UPROPERTY() class UButton* ResumeButton;
	UPROPERTY() class UButton* RetryGameButton;
};
