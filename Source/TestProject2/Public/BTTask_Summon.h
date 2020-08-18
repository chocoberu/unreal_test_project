// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Summon.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UBTTask_Summon : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Summon();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
