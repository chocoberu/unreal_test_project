// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemyCharacter.h"
#include "TestEnemyAnimInstance.h"
#include "TestWeapon.h"

// Sets default values
ATestEnemyCharacter::ATestEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WARRIOR(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		WARRIOR_ANIM(TEXT("/Game/Animations/WarriorEnemyBlueprint.WarriorEnemyBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	if (SK_WARRIOR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_WARRIOR.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TCharacter"));

	IsAttacking = false;
	HP = 100.0f;
}

// Called when the game starts or when spawned
void ATestEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FName WeaponSocket(TEXT("Hand_rSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<ATestWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurWeapon != nullptr)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		CurWeapon->SetActorRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	}
}

// Called every frame
void ATestEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TestAnim = Cast<UTestEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	TCHECK(TestAnim != nullptr);

	TestAnim->OnMontageEnded.AddDynamic(this, &ATestEnemyCharacter::OnAttackMontageEnded);
}

float ATestEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	SetDamage(FinalDamage);
	TLOG(Warning, TEXT("Actor : %s took Damage : %f, Current HP : %f"), *GetName(), FinalDamage, HP);
	return FinalDamage;
}

void ATestEnemyCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	TCHECK(IsAttacking);
	IsAttacking = false;
}

void ATestEnemyCharacter::Attack()
{
	if (IsAttacking)
		return;

	auto AnimInstance = Cast<UTestEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr)
		return;
	//AnimInstance-
	IsAttacking = true;
}
void ATestEnemyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			TLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

void ATestEnemyCharacter::SetDamage(float Damage)
{
	HP -= Damage;

	if (HP <= 0.0f)
	{
		TLOG(Warning, TEXT("DEAD!"));
		TestAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}
}

