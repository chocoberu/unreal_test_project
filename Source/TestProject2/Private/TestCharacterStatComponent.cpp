// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacterStatComponent.h"
#include "TestGameInstance.h"

// Sets default values for this component's properties
UTestCharacterStatComponent::UTestCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true; // 컴포넌트 초기화를 사용

}


// Called when the game starts
void UTestCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTestCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//SetStat(TEXT("Player"));
}

void UTestCharacterStatComponent::SetStat(FString Name)
{
	auto TestGameInstance = Cast<UTestGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	TCHECK(TestGameInstance != nullptr);
	CurrentStatData = TestGameInstance->GetTestCharacterData(Name);
	if (CurrentStatData != nullptr)
	{
		SetHP(CurrentStatData->MaxHP);
	}
}

void UTestCharacterStatComponent::SetDamage(float NewDamage)
{
	TCHECK(CurrentStatData != nullptr);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

float UTestCharacterStatComponent::GetAttack()
{
	TCHECK(CurrentStatData != nullptr, 0.0f);
	return CurrentStatData->Attack;
}
float UTestCharacterStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

void UTestCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UTestCharacterStatComponent::GetHPRatio()
{
	TCHECK(CurrentStatData != nullptr, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}




