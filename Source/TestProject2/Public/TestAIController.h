// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "AIController.h"
#include "TestAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATestAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey; // NPC 생성 위치를 찾기위한 키
	static const FName PatrolPosKey; // NPC의 순찰 위치를 찾기위한 키
	static const FName TargetKey; // 타겟을 찾기위한 키

	void RunAI(); // AI 가동
	void StopAI(); // AI 작동 중단
	
private:
	// 블랙보드 : 인공지능의 판단에 사용하는 데이터 집합
	// 비헤이비어 트리 : 블랙보드 데이터에 기반해 설계한 비헤이비어 트리의 정보를 저장
	UPROPERTY() class UBehaviorTree* BTAsset;
	UPROPERTY() class UBlackboardData* BBAsset;
};
