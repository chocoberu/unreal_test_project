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


// Sets default values
ATestEnemyCharacter::ATestEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	CharacterStat = CreateDefaultSubobject<UTestCharacterStatComponent>(TEXT("STAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));

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
	
	// HP Bar 관련 설정
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget>
		UI_HUD(TEXT("/Game/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	
	// AI Controller 관련
	AIControllerClass = ATestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	
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
	SetCharacterState(ECharacterState::LOADING);
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
void ATestEnemyCharacter::SetCharacterState(ECharacterState NewState)
{
	TCHECK(CurrentState != NewState);
	CurrentState = NewState;
	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = false;
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(false);
		bCanBeDamaged = true;

		CharacterStat->OnHPIsZero.AddLambda([this]() -> void
			{
				SetCharacterState(ECharacterState::DEAD);
			});
		auto CharacterWidget = Cast<UTestCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		TCHECK(CharacterWidget != nullptr);
		CharacterWidget->BindCharacterStat(CharacterStat);

		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		TestAIController->RunAI();
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		TestAnim->SetDeadAnim();
		bCanBeDamaged = false;

		TestAIController->StopAI();
		break;
	}
	}
}
ECharacterState ATestEnemyCharacter::GetCharacterState() const
{
	return CurrentState;
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
	SetCharacterState(ECharacterState::READY);
}
