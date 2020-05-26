// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Animation/AnimInstance.h"
#include "TestAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UTestAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayerFireMontage();
	void SetDeadAnim() { IsDead = true;  }
	
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
};
