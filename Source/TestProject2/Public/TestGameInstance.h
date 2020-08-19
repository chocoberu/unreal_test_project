// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "TestGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FTestCharacterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FTestCharacterData() : MaxHP(100.0f), Attack(35.0f), SkillAttack(100.0f){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") float SkillAttack;
};
/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTestGameInstance();

	virtual void Init() override;
	FTestCharacterData* GetTestCharacterData(FString Name);

	FStreamableManager StreamableManager; // 비동기 에셋 로딩을 위한 매니저
	void SetIsClear(bool bClear);
	bool GetIsClear();
private:
	
	UPROPERTY() class UDataTable* TestCharacterTable;
	UPROPERTY() bool bIsClear;
};
