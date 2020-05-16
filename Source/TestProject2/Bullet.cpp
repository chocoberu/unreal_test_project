// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 구체를 단순 콜리전 표현으로 사용합니다.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTMOVEMENT"));
	// 메시 초기화
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ST_BULLET(TEXT("/Game/ParagonWraith/FX/Meshes/Heroes/SM_Wraith_SimpleUltBullet.SM_Wraith_SimpleUltBullet"));

	if (ST_BULLET.Succeeded())
	{
		Mesh->SetStaticMesh(ST_BULLET.Object);
	}

	// 루트 컴포넌트를 콜리전 컴포넌트로 설정합니다.
	RootComponent = CollisionComponent;
	Mesh->SetupAttachment(RootComponent);
	// 구체의 콜리전 반경을 설정합니다.
	CollisionComponent->InitSphereRadius(5.0f);

	Mesh->SetRelativeScale3D(FVector(30.0f, 30.0f, 30.0f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 4000.0f;
	ProjectileMovementComponent->MaxSpeed = 4000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

