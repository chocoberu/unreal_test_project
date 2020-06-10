// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
	// 비헤이비어 트리의 Service Node 구현
public:
	UBTService_Detect();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
