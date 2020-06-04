// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWeapon.h"

// Sets default values
ATestWeapon::ATestWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Axes/Blade_DeadlyAxe/SK_Blade_DeadlyAxe.SK_Blade_DeadlyAxe"));

	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ATestWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

