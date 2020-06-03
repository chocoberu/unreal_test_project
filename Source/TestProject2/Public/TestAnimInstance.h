// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "Animation/AnimInstance.h"
#include "TestAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFireProjectileDelegate);
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
	void SetDeadAnim() { IsDead = true; }

	FOnFireProjectileDelegate OnFireProjectile;
	
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsFire;

	UFUNCTION()
		void AnimNotify_FireProjectile();
};
