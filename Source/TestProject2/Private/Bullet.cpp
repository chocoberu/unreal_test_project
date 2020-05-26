// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TestCharacter1.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ü�� �ܼ� �ݸ��� ǥ������ ����մϴ�.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	// �޽� �ʱ�ȭ
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ST_BULLET(TEXT("/Game/ParagonWraith/FX/Meshes/Heroes/SM_Wraith_SimpleUltBullet.SM_Wraith_SimpleUltBullet"));

	if (ST_BULLET.Succeeded())
	{
		Mesh->SetStaticMesh(ST_BULLET.Object);
	}

	// ��Ʈ ������Ʈ�� �ݸ��� ������Ʈ�� �����մϴ�.
	RootComponent = CollisionComponent;
	Mesh->SetupAttachment(RootComponent);
	// ��ü�� �ݸ��� �ݰ��� �����մϴ�.
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
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed; // �Ѿ��� �ӵ��� ����
	
	InitialLifeSpan = 2.0f; // 2�� �� �Ҹ�
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
	// �Ѿ��� �ӵ��� 0���� ����
	ProjectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
	SetActorEnableCollision(false);
	TLOG(Warning, *OtherActor->GetFName().ToString());
	Mesh->SetHiddenInGame(true); // �޽ø� ����
	FDamageEvent DamageEvent;
	
	if (OtherActor != GetOwner()) // ���� ����� �Ѿ��� �߻��� ĳ���Ͱ� �ƴ϶��
		OtherActor->TakeDamage(10.0f, DamageEvent, OwnerController, this); // ������ ����
	else
		TLOG(Warning, TEXT("I MY ME MINE"));
}

void ABullet::SetOwnerController(ATestCharacter1* TCharacter)
{
	OwnerController = TCharacter->GetController();
}

