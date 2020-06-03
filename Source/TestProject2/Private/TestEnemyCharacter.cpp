// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemyCharacter.h"
#include "TestEnemyAnimInstance.h"

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

	IsAttacking = false;
}

// Called when the game starts or when spawned
void ATestEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	auto AnimInstance = Cast<UTestEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	TCHECK(AnimInstance != nullptr);

	AnimInstance->OnMontageEnded.AddDynamic(this, &ATestEnemyCharacter::OnAttackMontageEnded);
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

