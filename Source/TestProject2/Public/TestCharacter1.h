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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void Fire();
	
	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABullet> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		ABullet* BulletClass;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
public:
	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm; // �������� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Camera) UCameraComponent* Camera; // ī�޶� ������Ʈ
	//UPROPERTY(VisibleAnywhere, Category = Weapon) USkeletalMeshComponent* Weapon;

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
	UPROPERTY(VisibleAnywhere, Category = Particle) UParticleSystemComponent* MuzzleParticle; // ��ƼŬ �ý���
	
	UPROPERTY(VisibleAnywhere, Category = TEST) FVector PlayerDirection;
};
