// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Animation/AnimInstance.h"
#include "TestEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTestEnemyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackingMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;
};
