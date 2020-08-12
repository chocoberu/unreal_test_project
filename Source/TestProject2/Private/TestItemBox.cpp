// Fill out your copyright notice in the Description page of Project Settings.


#include "TestItemBox.h"
#include "TestCharacter1.h"

// Sets default values
ATestItemBox::ATestItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

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

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));

	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}
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
	TLOG_S(Warning);

	auto TestCharacter = Cast<ATestCharacter1>(OtherActor);
	TCHECK(TestCharacter != nullptr);

	if (TestCharacter != nullptr)
	{
		// TODO : 아이템 접촉시 아이템 습득 구현필요 (HP 회복, 총알 개수 증가 등)
		TestCharacter->SetHPPlus(50.0f);
		Effect->Activate(true);
		Box->SetHiddenInGame(true, true);
		SetActorEnableCollision(false);
		Effect->OnSystemFinished.AddDynamic(this, &ATestItemBox::OnEffectFinished);
	}

}
void ATestItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}
