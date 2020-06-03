// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBaseCharacter.h"

// Sets default values
ATestBaseCharacter::ATestBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

