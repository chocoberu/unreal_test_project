// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBossAnimInstance.h"

UTestBossAnimInstance::UTestBossAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		ATTACK_MONTAGE(TEXT("/Game/Animations/SK_Mannequin_BossNormalAttack.SK_Mannequin_BossNormalAttack"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		NormalAttackMontage = ATTACK_MONTAGE.Object;
	}
	IsDead = false;
}
void UTestBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UTestBossAnimInstance::PlayAttackingMontage()
{
	TCHECK(!IsDead);
	if (!Montage_IsPlaying(NormalAttackMontage))
		Montage_Play(NormalAttackMontage, 1.0f);
}

void UTestBossAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
