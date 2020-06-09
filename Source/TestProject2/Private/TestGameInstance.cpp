// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameInstance.h"

UTestGameInstance::UTestGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		DT_TESTCHARACTER(TEXT("/Game/GameData/TestCharacterData.TestCharacterData"));
	if (DT_TESTCHARACTER.Succeeded())
		TestCharacterTable = DT_TESTCHARACTER.Object;
}
void UTestGameInstance::Init()
{
	Super::Init();
	TLOG(Warning, TEXT("Player Attack : %f"), GetTestCharacterData(TEXT("Player"))->Attack);
}

FTestCharacterData * UTestGameInstance::GetTestCharacterData(FString Name)
{
	return TestCharacterTable->FindRow<FTestCharacterData>(*Name,TEXT(""));
}
