// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBaseCharacter.h"
#include "TestCharacterWidget.h"
#include "Components/WidgetComponent.h"
#include "TestCharacterStatComponent.h"

// Sets default values
ATestBaseCharacter::ATestBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	CharacterStat = CreateDefaultSubobject<UTestCharacterStatComponent>(TEXT("STAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));

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

	// 공격 범위 관련
	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void ATestBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATestBaseCharacter::GetAttackRange() const
{
	return AttackRange;
}

float ATestBaseCharacter::GetAttackRadius() const
{
	return AttackRadius;
}

void ATestBaseCharacter::SetCharacterState(ECharacterState NewState)
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
		RunAI();
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = false;

		SetDead();
		break;
	}
	}
}

ECharacterState ATestBaseCharacter::GetCharacterState() const
{
	return CurrentState;
}

void ATestBaseCharacter::RunAI()
{
}

void ATestBaseCharacter::SetDead()
{
}
