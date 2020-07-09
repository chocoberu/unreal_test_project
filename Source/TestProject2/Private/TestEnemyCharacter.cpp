// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemyCharacter.h"
#include "TestEnemyAnimInstance.h"
#include "TestWeapon.h"
#include "TestCharacterStatComponent.h"
#include "Components/WidgetComponent.h"
#include "TestCharacterWidget.h"
#include "TestAIController.h"
#include "TestEnemyCharacterSetting.h"
#include "TestGameInstance.h"
#include "DrawDebugHelpers.h"


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

	//IsAttacking = false;
	
	// AI Controller 관련
	AIControllerClass = ATestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 공격 범위 관련
	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void ATestEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	auto DefaultSetting = GetDefault<UTestEnemyCharacterSetting>();
	int32 RandomIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	CharacterAssetToLoad = DefaultSetting->CharacterAssets[RandomIndex];

	auto TestGameInstance = Cast<UTestGameInstance>(GetGameInstance());
	if (TestGameInstance != nullptr)
	{
		AssetStreamingHandle = TestGameInstance->StreamableManager.RequestAsyncLoad(CharacterAssetToLoad, 
			FStreamableDelegate::CreateUObject(this, &ATestEnemyCharacter::OnAssetLoadCompleted));
	}

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

	TestAIController = Cast<ATestAIController>(GetController());
	SetCharacterState(ECharacterState::LOADING); //
	
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

	CharacterStat->SetStat(TEXT("Enemy1"));
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		TLOG(Warning, TEXT("Enemy1 OnHPIsZero"));
		TestAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
	TestAnim->OnMontageEnded.AddDynamic(this, &ATestEnemyCharacter::OnAttackMontageEnded);
	TestAnim->OnAttackHitCheck.AddUObject(this, &ATestEnemyCharacter::AttackCheck);
}

float ATestEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TLOG(Warning, TEXT("Actor : %s took Damage : %f, Current HP : %f"), *GetName(), FinalDamage, CharacterStat->GetCurrentHP());
	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}

void ATestEnemyCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	TCHECK(IsAttacking);
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void ATestEnemyCharacter::Attack()
{
	if (IsAttacking)
		return;

	TestAnim->PlayAttackingMontage();
	IsAttacking = true;
}

void ATestEnemyCharacter::AttackCheck()
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

void ATestEnemyCharacter::OnAssetLoadCompleted()
{
	USkeletalMesh* AssetLoaded = Cast<USkeletalMesh>(AssetStreamingHandle->GetLoadedAsset()); // 불러온 스켈레탈 메시
	AssetStreamingHandle.Reset(); // 핸들 초기화
	if (AssetLoaded != nullptr)
	{
		GetMesh()->SetSkeletalMesh(AssetLoaded);
	}
	TLOG(Warning, TEXT("AssetLoad Completeed"));
	SetCharacterState(ECharacterState::READY);
}

void ATestEnemyCharacter::RunAI()
{
	TLOG(Warning, TEXT("Run Enmey AI!"));
	TestAIController->RunAI();
}

void ATestEnemyCharacter::SetDead()
{
	TestAnim->SetDeadAnim();
	TestAIController->StopAI();
}
