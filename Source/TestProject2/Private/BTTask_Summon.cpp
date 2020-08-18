// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Summon.h"
#include "TestEnemyCharacter.h"
#include "TestBossCharacter.h"
#include "TestBossAIController.h"
#include "TestCharacter1.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Summon::UBTTask_Summon()
{
	NodeName = TEXT("Summon");
}

EBTNodeResult::Type UBTTask_Summon::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Boss = Cast<ATestBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto Target = Cast<ATestCharacter1>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if(Boss == nullptr)
		return EBTNodeResult::Failed;
	if(Target == nullptr)
		return EBTNodeResult::Failed;

	//FVector TargetPos = Target->GetActorLocation();
	//FVector Offset = Target->GetActorForwardVector();

	//Offset.X *= 300.0f;
	//Offset.Y *= 300.0f;
	//TargetPos -= Offset;

	for(int i = 0; i < 2; i++)
		GetWorld()->SpawnActor<ATestEnemyCharacter>(Boss->GetActorLocation(), FRotator::ZeroRotator);

	return EBTNodeResult::Succeeded;
}
