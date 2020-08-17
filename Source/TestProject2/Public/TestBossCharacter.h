// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "TestBaseCharacter.h"
#include "TestBossCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTeleportEndDelegate);
//DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestBossCharacter : public ATestBaseCharacter
{
	GENERATED_BODY()
	
public:
	ATestBossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnAssetLoadCompleted();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();
	void Teleport(FVector TargetPos);

	FOnTeleportEndDelegate OnTeleportEnd;

protected:
	virtual void RunAI();
	virtual void SetDead();

private:
	UPROPERTY()
		class ATestBossAIController* TestBossController; // ���� ĳ������ AIController
	UPROPERTY() class UTestEnemyAnimInstance* TestAnim; // �ӽ� �ִ� �ν��Ͻ�

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackCheck();


};
