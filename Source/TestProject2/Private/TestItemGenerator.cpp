// Fill out your copyright notice in the Description page of Project Settings.

#include "TestItemGenerator.h"
#include "TestItemBox.h"

// Sets default values
ATestItemGenerator::ATestItemGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemBoxSpawnTime = 20.0f;
}

// Called when the game starts or when spawned
void ATestItemGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]()-> void {

		FVector2D RandXY = FMath::RandPointInCircle(800.0f);
		GetWorld()->SpawnActor<ATestItemBox>(GetActorLocation() + FVector(RandXY, 160.0f), FRotator::ZeroRotator);
		TLOG(Warning, TEXT("Spawn ItemBox"));
		}), ItemBoxSpawnTime, true);
}

// Called every frame
void ATestItemGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

