// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestEnemyCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=TestProject2)
class TESTPROJECT2SETTING_API UTestEnemyCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UTestEnemyCharacterSetting();

	UPROPERTY(config) TArray<FSoftObjectPath> CharacterAssets;
};
