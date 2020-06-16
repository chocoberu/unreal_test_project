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

	static const FName HomePosKey; // NPC ���� ��ġ�� ã������ Ű
	static const FName PatrolPosKey; // NPC�� ���� ��ġ�� ã������ Ű
	static const FName TargetKey; // Ÿ���� ã������ Ű

	void RunAI(); // AI ����
	void StopAI(); // AI �۵� �ߴ�
	
private:
	// ������ : �ΰ������� �Ǵܿ� ����ϴ� ������ ����
	// �����̺�� Ʈ�� : ������ �����Ϳ� ����� ������ �����̺�� Ʈ���� ������ ����
	UPROPERTY() class UBehaviorTree* BTAsset;
	UPROPERTY() class UBlackboardData* BBAsset;
};
