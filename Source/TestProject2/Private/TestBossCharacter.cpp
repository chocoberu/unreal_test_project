// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBossCharacter.h"
#include "TestEnemyAnimInstance.h"
#include "TestWeapon.h"
#include "TestCharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "TestCharacterWidget.h"
#include "TestAIController.h"
#include "TestEnemyCharacterSetting.h"
#include "TestGameInstance.h"

ATestBossCharacter::ATestBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 공격 범위 관련
	AttackRadius = 250.0f;
	AttackRange = 250.0f;
}
void ATestBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATestBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestBossCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterStat->SetStat(TEXT("Boss"));
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		TLOG(Warning, TEXT("Enemy1 OnHPIsZero"));
		TestAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
}

float ATestBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TLOG(Warning, TEXT("Actor : %s took Damage : %f, Current HP : %f"), *GetName(), FinalDamage, CharacterStat->GetCurrentHP());
	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}
void ATestBossCharacter::OnAssetLoadCompleted()
{
	SetCharacterState(ECharacterState::READY);

	GetCapsuleComponent()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
}