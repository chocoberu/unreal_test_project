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
	
	// 스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> ProjectileClass;;
public:
	UPROPERTY(VisibleAnywhere, Category = Camera) USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera) UCameraComponent* Camera;
	//UPROPERTY(VisibleAnywhere, Category = Weapon) USkeletalMeshComponent* Weapon;

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

	UPROPERTY() class UTestAnimInstance* TestAnim;
};
