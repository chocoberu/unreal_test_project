// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter1.h"
#include "TestAnimInstance.h"
#include "Bullet.h"

// Sets default values
ATestCharacter1::ATestCharacter1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �������� ������Ʈ, ī�޶� ������Ʈ�� ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// ���������� ��Ʈ ������Ʈ�� ����
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm); // ī�޶� �������Ͽ� ����

	GetCapsuleComponent()->SetCapsuleHalfHeight(95.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -97.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WRAITH(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (SK_WRAITH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_WRAITH.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		WRAITH_ANIM(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Wraith_AnimBlueprint.Wraith_AnimBlueprint_C"));
	if (WRAITH_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WRAITH_ANIM.Class);
	}
	/*static ConstructorHelpers::FClassFinder<ABullet>
		C_BULLET(TEXT("/Script/TestProject2.Bullet_C"));
	if (C_BULLET.Succeeded())
	{
		TLOG(Warning, TEXT("Success"));
		ProjectileClass = C_BULLET.Class;
	}*/

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 700.0f;

	// �׽�Ʈ �ڵ�
	ArmLengthTo = 450.f;
	SpringArm->bUsePawnControlRotation = true; // ���� ��� �����ϵ��� ����
	SpringArm->bInheritPitch = true; // ��ġ, ��, ���� ��� ��� ����
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true; // �浹 �׽�Ʈ�� �ϵ��� ����
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

}

// Called when the game starts or when spawned
void ATestCharacter1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TargetArmLength���� ArmLengthTo�� �����Ѵ�.
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
}

// Called to bind functionality to input
void ATestCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ��ǲ������Ʈ�� �̵� ���� �Լ��� ���´�
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

	FName MuzzleSocket(TEXT("Muzzle_01")); // ���̷�Ż �޽��� muzzle ������ �����Ѵٸ�
	if (GetMesh()->DoesSocketExist(MuzzleSocket))
	{
		// �ش� ��ġ���� �÷��̾��� ȸ���������� �Ѿ� ����
		BulletClass = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), GetMesh()->GetSocketLocation(MuzzleSocket),GetCapsuleComponent()->GetRelativeRotation());
	}
}

void ATestCharacter1::MoveForward(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void ATestCharacter1::MoveRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void ATestCharacter1::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue); // Pitch�� Y�� ȸ��
}

void ATestCharacter1::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue); // Yaw�� Z�� ȸ��
}

