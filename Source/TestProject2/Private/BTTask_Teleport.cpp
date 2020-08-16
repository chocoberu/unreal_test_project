// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Teleport.h"
#include "TestBossCharacter.h"
#include "TestBossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TestCharacter1.h"

UBTTask_Teleport::UBTTask_Teleport()
{
	NodeName = TEXT("Teleport");
	bNotifyTick = false; // TickTask가 호출되도록 설정
}

EBTNodeResult::Type UBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	TLOG(Warning, TEXT("Teleport Start"));
	auto TestBoss = Cast<ATestBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (TestBoss == nullptr)
	{
		TLOG(Error, TEXT("Self not found"));
		return EBTNodeResult::Failed;
	}

	TLOG(Warning, TEXT("Target"));
	auto Target = Cast<ATestCharacter1>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
	{
		TLOG(Error, TEXT("target not found"));
		return EBTNodeResult::Failed;
	}
	
	// 플레이어 뒤쪽으로 텔레포트

	FVector TargetPos = Target->GetActorLocation();
	FVector Offset = Target->GetActorForwardVector();
	TLOG(Warning, TEXT("Location (%f, %f, %f)"), TargetPos.X, TargetPos.Y, TargetPos.Z);
	TLOG(Warning, TEXT("Offset (%f, %f, %f)"), Offset.X, Offset.Y, Offset.Z);
	Offset.X *= 300.0f;
	Offset.Y *= 300.0f;
	TargetPos -= Offset;
	TLOG(Warning, TEXT("Offset (%f, %f, %f)"), Offset.X, Offset.Y, Offset.Z);

	TLOG(Warning, TEXT("Location (%f, %f, %f)"),TargetPos.X, TargetPos.Y, TargetPos.Z);
	TestBoss->Teleport(TargetPos);
	return EBTNodeResult::Succeeded;
}

void UBTTask_Teleport::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	//
}
