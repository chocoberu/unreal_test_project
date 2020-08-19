// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "TestGamePlayWidget.h"
#include "TestGamePlayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestGamePlayResultWidget : public UTestGamePlayWidget
{
	GENERATED_BODY()
public:

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY() class UTextBlock* Result;
	UPROPERTY() class UTextBlock* TotalScore;
};
