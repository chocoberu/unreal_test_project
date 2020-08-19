// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/Actor.h"
#include "TestItemGenerator.generated.h"

UCLASS()
class TESTPROJECT2_API ATestItemGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestItemGenerator();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClearTimerHandle();

private:
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAcess = true))
	float ItemBoxSpawnTime;

	FTimerHandle SpawnItemBoxTimerHandle = {};
};
