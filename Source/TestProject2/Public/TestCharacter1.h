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

	enum class ECameraMode // ī�޶� ���
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

	void SetHPPlus(float PlusHP);
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

public:
	UPROPERTY(EditDefaultsOnly, Category = Projectile) // �Ѿ� Ŭ���� 
		class ABullet* BulletClass;
	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm; // �������� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Camera) UCameraComponent* Camera; // ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Stat) class UTestCharacterStatComponent* CharacterStat; // ĳ���� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = UI) class UWidgetComponent* HPBarWidget; // HP�� ����

protected:

	// �������� ���� ����
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	UPROPERTY() class UTestAnimInstance* TestAnim; // �ִ� �ν��Ͻ�
	UPROPERTY(VisibleAnywhere, Category = Particle) UParticleSystemComponent* MuzzleParticle; // �Ѿ� �߻� ���� ��ƼŬ �ý���
	
	UPROPERTY(VisibleAnywhere, Category = TEST) FVector PlayerDirection; // �÷��̾ �ٶ󺸴� ����
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ECharacterState CurrentState;

	UPROPERTY() class ATestPlayerController* TestPlayerController;
};
