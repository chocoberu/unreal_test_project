// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "TestAIController.h"
#include "TestCharacter1.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f; // TickNode 호출 간격
}
void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// NPC의 위치를 기준으로 반경 3미터 내에 캐릭터가 있는지 감지
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn(); // AIController가 조종하는 폰
	if (ControllingPawn == nullptr)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation(); // 폰의 위치 좌표
	float DetectRadius = 1000.0f; // 300

	if (World == nullptr)
		return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	// Center 기준으로 반경 3미터 내를 탐지
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
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATestAIController::TargetKey, nullptr); // 타겟을 초기화
		for (auto& OverlapResult : OverlapResults) // 충돌한 객체들 중에서 플레이어를 찾기
		{
			ATestCharacter1* ATestCharacter = Cast<ATestCharacter1>(OverlapResult.GetActor());
			if (ATestCharacter && ATestCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATestAIController::TargetKey, ATestCharacter); // 타겟을 플레이어로 설정

				// DrawDebug 
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, ATestCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ATestCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
			}
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
