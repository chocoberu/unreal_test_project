// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/Character.h"
#include "TestCharacter1.generated.h"

UCLASS()
class TESTPROJECT2_API ATestCharacter1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class ECameraMode // 카메라 모드
	{
		GTA,
		DIABLO
	};
	void SetCameraMode(ECameraMode NewCameraMode);
	ECameraMode CurrentCameraMode;
	FVector DirectionToMove = FVector::ZeroVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
public:
	UPROPERTY(EditDefaultsOnly, Category = Projectile) // 총알 클래스 
		class ABullet* BulletClass;
	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm; // 스프링암 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Camera) UCameraComponent* Camera; // 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Stat) class UTestCharacterStatComponent* CharacterStat; // 캐릭터 스탯 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = UI) class UWidgetComponent* HPBarWidget; // HP바 위젯

protected:

	// 스프링암 관련 변수
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	UPROPERTY() class UTestAnimInstance* TestAnim; // 애님 인스턴스
	UPROPERTY(VisibleAnywhere, Category = Particle) UParticleSystemComponent* MuzzleParticle; // 총알 발사 시의 파티클 시스템
	
	UPROPERTY(VisibleAnywhere, Category = TEST) FVector PlayerDirection; // 플레이어가 바라보는 방향
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;
};
