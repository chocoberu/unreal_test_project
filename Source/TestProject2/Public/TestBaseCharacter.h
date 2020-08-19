// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/Character.h"
#include "TestBaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

/*
TestEnemyCharacter, TestBossCharacter�� ���̽� Ŭ����
*/

UCLASS()
class TESTPROJECT2_API ATestBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Stat) class UTestCharacterStatComponent* CharacterStat; // ĳ���� ����
	UPROPERTY(VisibleAnywhere, Category = UI) class UWidgetComponent* HPBarWidget; // HP�� ����

	FOnAttackEndDelegate OnAttackEnd;

	float GetAttackRange() const;
	float GetAttackRadius() const;

	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	virtual void SetDead();

protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ECharacterState CurrentState;

	virtual void RunAI();
	
};
