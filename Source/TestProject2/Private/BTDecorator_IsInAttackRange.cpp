// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "TestAIController.h"
#include "TestCharacter1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TestEnemyCharacter.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}
bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;

	auto Target = Cast<ATestCharacter1>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATestAIController::TargetKey)); // 타겟인 플레이어
	if (Target == nullptr)
		return false;

	float AttackRange = Cast<ATestEnemyCharacter>(ControllingPawn)->GetAttackRange();
	TLOG(Warning, TEXT("Attack Range is %f"), AttackRange);
	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);
	return bResult;
}
