// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "TestEnemyCharacter.h"
#include "TestBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestBossCharacter : public ATestEnemyCharacter
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

};
