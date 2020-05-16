// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TESTPROJECT2_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 발사체의 속도를 발사 방향으로 초기화시킵니다.
	void FireInDirection(const FVector& ShootDirection);

	// 스태틱메시 컴포넌트
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	// 구체 콜리전 컴포넌트입니다.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// 프로젝타일 무브먼트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;
};
