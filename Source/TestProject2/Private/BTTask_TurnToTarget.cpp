// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "TestAIController.h"
#include "TestEnemyCharacter.h"
#include "TestCharacter1.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}
EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TestEnemy = Cast<ATestEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (TestEnemy == nullptr)
		return EBTNodeResult::Failed;

	auto Target = Cast<ATestCharacter1>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATestAIController::TargetKey));
	if(Target == nullptr)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - TestEnemy->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	TestEnemy->SetActorRotation(FMath::RInterpTo(TestEnemy->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
