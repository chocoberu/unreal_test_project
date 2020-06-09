// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Blueprint/UserWidget.h"
#include "TestCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UTestCharacterStatComponent* NewCharacterStat);
protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
private:
	TWeakObjectPtr<class UTestCharacterStatComponent> CurrentCharacterStat;
	UPROPERTY() class UProgressBar* HPProgressBar;
};
