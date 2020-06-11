// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
	// 공격 처리하는 BTTaskNode
	// 공격 태스크는 공격 애니메이션이 끝날때 까지 대기하는 지연 태스크이므로 
	// ExecuteTask 결과 값을 InProgress(진행중)을오 반환하고 공격이 끝났을 때 태스크가 끝났다고 알려줘야함
	// FinishLatentTask로 알릴 수 있음.
public:
	UBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;
};
