// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter1.h"
#include "TestAnimInstance.h"
#include "Bullet.h"

// Sets default values
ATestCharacter1::ATestCharacter1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링암 컴포넌트, 카메라 컴포넌트, 파티클 시스템 컴포넌트를 생성
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	MuzzleParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));

	// 스프링암을 루트 컴포넌트에 붙임
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm); // 카메라를 스프링암에 붙임
	FName MuzzleSocket(TEXT("Muzzle_01"));
	MuzzleParticle->SetupAttachment(GetMesh(), MuzzleSocket);

	GetCapsuleComponent()->SetCapsuleHalfHeight(95.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TCharacter")); // 콜리전 프리셋을 TCharacter로 변경

	// 메시의 상대 위치, 회전 적용
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -97.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f; // 스프링암 설정
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WRAITH(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (SK_WRAITH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_WRAITH.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		WRAITH_ANIM(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Wraith_AnimTest.Wraith_AnimTest_C"));
	if (WRAITH_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WRAITH_ANIM.Class);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PT_MUZZLE_FLASH(TEXT("/Game/ParagonWraith/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash"));
	if (PT_MUZZLE_FLASH.Succeeded())
	{
		MuzzleParticle->SetTemplate(PT_MUZZLE_FLASH.Object);
	}
	MuzzleParticle->bAllowRecycling = true; // Allow Recycling 활성화

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 700.0f;

	// 테스트 코드
	PlayerDirection = GetActorForwardVector();

	SetCameraMode(ECameraMode::GTA);
	HP = 100.0f;
}

// Called when the game starts or when spawned
void ATestCharacter1::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestCharacter1::SetCameraMode(ECameraMode NewCameraMode)
{
	CurrentCameraMode = NewCameraMode;
	switch (CurrentCameraMode)
	{
	case ECameraMode::DIABLO:
		SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		break;
	case ECameraMode::GTA:
		ArmLengthTo = 450.f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called every frame
void ATestCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentCameraMode)
	{
	case ECameraMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
	// 스프링 암의 TargetArmLength에서 ArmLengthTo로 보간한다.
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
}

// Called to bind functionality to input
void ATestCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 인풋컴포넌트에 이동 관련 함수를 묶는다
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestCharacter1::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestCharacter1::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATestCharacter1::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATestCharacter1::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATestCharacter1::Fire);
}

void ATestCharacter1::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TestAnim = Cast<UTestAnimInstance>(GetMesh()->GetAnimInstance());
}

void ATestCharacter1::Fire()
{
	TLOG(Warning, TEXT("Fire!"));
	TestAnim->PlayerFireMontage();

	FName MuzzleSocket(TEXT("Muzzle_01")); // 스켈레탈 메시의 muzzle 소켓이 존재한다면
	if (GetMesh()->DoesSocketExist(MuzzleSocket))
	{
		//FRotator TempRotator = FRotator::MakeFromEuler(PlayerDirection);
		//SetActorRotation(TempRotator);
		MuzzleParticle->Activate(true); // 파티클 시스템 활성화
		// 해당 위치에서 플레이어의 회전방향으로 총알 생성
		BulletClass = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), GetMesh()->GetSocketLocation(MuzzleSocket),GetCapsuleComponent()->GetRelativeRotation());
		BulletClass->SetOwner(this);
		BulletClass->SetOwnerController(this);
	}
}

float ATestCharacter1::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	SetDamage(FinalDamage);
	return FinalDamage;
}


// 입력 관련 함수
void ATestCharacter1::MoveForward(float NewAxisValue)
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case ECameraMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
}

void ATestCharacter1::MoveRight(float NewAxisValue)
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case ECameraMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
}

void ATestCharacter1::LookUp(float NewAxisValue)
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::GTA:
		AddControllerPitchInput(NewAxisValue); // Pitch가 Y축 회전
		break;
	}
}

void ATestCharacter1::Turn(float NewAxisValue)
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::GTA:
		AddControllerYawInput(NewAxisValue); // Yaw가 Z축 회전
		break;
	}
	PlayerDirection = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X); // PlayerDirection에 카메라 방향을 저장
	//FRotator TempRotator = FRotator::MakeFromEuler(PlayerDirection);
	//SetActorRotation(TempRotator);
}

void ATestCharacter1::SetDamage(float Damage)
{
	HP -= Damage;

	if (HP <= 0.0f)
	{
		TestAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}
}

