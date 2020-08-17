// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossNormalAttack.h"
#include "TestBossAIController.h"
#include "TestBossCharacter.h"

UBTTask_BossNormalAttack::UBTTask_BossNormalAttack()
{
	bNotifyTick = true; //
	IsAttacking = false;
}
EBTNodeResult::Type UBTTask_BossNormalAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TestBoss = Cast<ATestBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (TestBoss == nullptr)
		return EBTNodeResult::Failed;
	TestBoss->Attack();
	IsAttacking = true;
	TestBoss->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
		});
	return EBTNodeResult::InProgress;
}

void UBTTask_BossNormalAttack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
