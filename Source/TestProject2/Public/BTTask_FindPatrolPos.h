// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
	// 비헤이비어 트리의 Task Node 구현
public:
	UBTTask_FindPatrolPos();

	// 비헤이비어 트리는 태스크 실행 시 ExecuteTask 호출
	// Aborted(태스크 중단), Failed(태스크 실패), Succeeded, InProgress(태스크 수행중)의 값을 반환
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
