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
	
	// �����̺�� Ʈ���� Task Node ����
public:
	UBTTask_FindPatrolPos();

	// �����̺�� Ʈ���� �½�ũ ���� �� ExecuteTask ȣ��
	// Aborted(�½�ũ �ߴ�), Failed(�½�ũ ����), Succeeded, InProgress(�½�ũ ������)�� ���� ��ȯ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
