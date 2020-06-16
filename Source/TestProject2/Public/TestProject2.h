// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT, // 캐릭터 생성 전 스테이트
	LOADING, // 캐릭터 애셋을 로딩하는 스테이트
	READY, // 캐릭터 애셋 로딩이 완료된 스테이트
	DEAD // 캐릭터 사망시 스테이트
};
DECLARE_LOG_CATEGORY_EXTERN(TestProject2, Log, All);
#define TLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TLOG_S(Verbosity) UE_LOG(TestProject2, Verbosity, TEXT("%s"),  *TLOG_CALLINFO)
#define TLOG(Verbosity, Format, ...) UE_LOG(TestProject2, Verbosity, TEXT("%s %s"), *TLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define TCHECK(Expr, ...) { if(!(Expr)) {TLOG(Error,TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }