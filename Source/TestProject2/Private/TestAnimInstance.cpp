// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAnimInstance.h"

UTestAnimInstance::UTestAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
		FIRE_MONTAGE(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Animations/Fire_A_Slow_Montage.Fire_A_Slow_Montage"));
	if (FIRE_MONTAGE.Succeeded())
	{
		FireMontage = FIRE_MONTAGE.Object;
	}
	IsDead = false;
}
void UTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UTestAnimInstance::PlayerFireMontage()
{
	TCHECK(!IsDead);
	Montage_Play(FireMontage, 1.0f);
}
