// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBossCharacter.h"
#include "TestEnemyAnimInstance.h"
#include "TestWeapon.h"
#include "TestCharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "TestCharacterWidget.h"
#include "TestBossAIController.h"
#include "TestEnemyCharacterSetting.h"
#include "TestGameInstance.h"
#include "DrawDebugHelpers.h"

ATestBossCharacter::ATestBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 메시, 애니메이션 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WARRIOR(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	// TODO : 애니메이션 파일 교체
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

	// AI Controller 관련
	AIControllerClass = ATestBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 공격 범위 관련
	AttackRange = 500.0f; //200
	AttackRadius = 1000.0f; // 100
}
void ATestBossCharacter::BeginPlay()
{
	Super::BeginPlay();

	FName WeaponSocket(TEXT("Hand_rSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<ATestWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurWeapon != nullptr)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		CurWeapon->SetActorRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	}

	auto CharacterWidget = Cast<UTestCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	TCHECK(CharacterWidget != nullptr);
	CharacterWidget->BindCharacterStat(CharacterStat); // 캐릭터 스탯 설정

	TestBossController = Cast<ATestBossAIController>(GetController());
	
	OnAssetLoadCompleted();
}

void ATestBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestBossCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// TODO : 보스 애님 인스턴스로 교체
	TestAnim = Cast<UTestEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	CharacterStat->SetStat(TEXT("Boss"));
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		TLOG(Warning, TEXT("Boss OnHPIsZero"));
		TestAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
	TestAnim->OnMontageEnded.AddDynamic(this, &ATestBossCharacter::OnAttackMontageEnded);
	TestAnim->OnAttackHitCheck.AddUObject(this, &ATestBossCharacter::AttackCheck);
}

float ATestBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TLOG(Warning, TEXT("Actor : %s took Damage : %f, Current HP : %f"), *GetName(), FinalDamage, CharacterStat->GetCurrentHP());
	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}
void ATestBossCharacter::Attack()
{
	if (IsAttacking)
		return;

	TestAnim->PlayAttackingMontage();
	IsAttacking = true;
}
void ATestBossCharacter::Teleport(FVector TargetPos)
{
	SetActorLocation(TargetPos);
}
void ATestBossCharacter::RunAI()
{
	TestBossController->RunAI();
}
void ATestBossCharacter::SetDead()
{
	TestAnim->SetDeadAnim();
	TestBossController->StopAI();
}

void ATestBossCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	TCHECK(IsAttacking);
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}
void ATestBossCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	// 공격 판정을 디버그 드로우
#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 2.5f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			//TODO take
			TLOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}
void ATestBossCharacter::OnAssetLoadCompleted()
{
	SetCharacterState(ECharacterState::READY);

	GetCapsuleComponent()->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
}