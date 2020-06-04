// Fill out your copyright notice in the Description page of Project Settings.


#include "TestItemBox.h"

// Sets default values
ATestItemBox::ATestItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}
	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
}

// Called when the game starts or when spawned
void ATestItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATestItemBox::OnCharacterOverlap);
}

// Called every frame
void ATestItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// TODO : 아이템 접촉시 아이템 습득 구현필요 (HP 회복, 총알 개수 증가 등)
	TLOG_S(Warning);
}

