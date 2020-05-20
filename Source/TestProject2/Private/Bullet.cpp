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
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
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
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Bullet"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	Mesh->SetRelativeScale3D(FVector(20.0f, 20.0f, 20.0f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 4000.0f;
	ProjectileMovementComponent->MaxSpeed = 4000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed; // 총알의 속도를 조절
	
	InitialLifeSpan = 2.0f; // 2초 후 소멸
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

void ABullet::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// 총알의 속도를 0으로 설정
	ProjectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
	SetActorEnableCollision(false);
	TLOG(Warning, *OtherActor->GetFName().ToString());
}

