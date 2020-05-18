// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

ATestPlayerController::ATestPlayerController()
{

}
void ATestPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATestPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
}
