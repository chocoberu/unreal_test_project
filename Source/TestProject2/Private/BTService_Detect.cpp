// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "TestAIController.h"
#include "TestCharacter1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f; // TickNode ȣ�� ����
}
void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// NPC�� ��ġ�� �������� �ݰ� 3���� ���� ĳ���Ͱ� �ִ��� ����
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn(); // AIController�� �����ϴ� ��
	if (ControllingPawn == nullptr)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation(); // ���� ��ġ ��ǥ
	float DetectRadius = 300.0f;

	if (World == nullptr)
		return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	// Center �������� �ݰ� 3���� ���� Ž��
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATestAIController::TargetKey, nullptr); // Ÿ���� �ʱ�ȭ
		for (auto& OverlapResult : OverlapResults) // �浹�� ��ü�� �߿��� �÷��̾ ã��
		{
			ATestCharacter1* ATestCharacter = Cast<ATestCharacter1>(OverlapResult.GetActor());
			if (ATestCharacter && ATestCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATestAIController::TargetKey, ATestCharacter); // Ÿ���� �÷��̾�� ����

				// DrawDebug 
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, ATestCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ATestCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
			}
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
