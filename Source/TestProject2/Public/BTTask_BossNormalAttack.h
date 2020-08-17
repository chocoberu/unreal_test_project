// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossNormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UBTTask_BossNormalAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossNormalAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsAttacking = false;
};
