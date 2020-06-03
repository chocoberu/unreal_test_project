// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAnimInstance.h"

UTestAnimInstance::UTestAnimInstance()
{
	//static ConstructorHelpers::FObjectFinder<UAnimMontage>
		//FIRE_MONTAGE(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Animations/Fire_A_Slow_Montage.Fire_A_Slow_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		FIRE_MONTAGE(TEXT("/Game/Animations/Wraith_Skeleton_Montage.Wraith_Skeleton_Montage"));
	if (FIRE_MONTAGE.Succeeded())
	{
		FireMontage = FIRE_MONTAGE.Object;
	}
	IsDead = false;
	IsFire = false;
}
void UTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UTestAnimInstance::PlayerFireMontage()
{
	// TODO: Fire 애니메이션 수정필요
	TCHECK(!IsDead);
	//IsFire = true;
	Montage_Play(FireMontage, 1.0f); 
	
}

void UTestAnimInstance::AnimNotify_FireProjectile()
{
	TLOG(Warning, TEXT("Projectile"));
	OnFireProjectile.Broadcast();
}
