// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProject2.h"
#include "GameFramework/Character.h"
#include "TestEnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class TESTPROJECT2_API ATestEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere, Category = Stat) class UTestCharacterStatComponent* CharacterStat; // ƒ≥∏Ø≈Õ Ω∫≈»
	UPROPERTY(VisibleAnywhere, Category = UI) class UWidgetComponent* HPBarWidget; // HPπŸ ¿ß¡¨

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
	void SetCharacterState(ECharacterState NewState);
	ECharacterState GetCharacterState() const;

	float GetAttackRange() const;
	float GetAttackRadius() const;

protected:
	UPROPERTY() class UTestEnemyAnimInstance* TestAnim; // æ÷¥‘ ¿ŒΩ∫≈œΩ∫
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual void AttackCheck();

	virtual void OnAssetLoadCompleted();

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;

	int32 AssetIndex = 0;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ECharacterState CurrentState;
	UPROPERTY()
		class ATestAIController* TestAIController;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

};
