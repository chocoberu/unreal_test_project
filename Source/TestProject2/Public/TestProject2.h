// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TestProject2, Log, All);
#define TLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TLOG_S(Verbosity) UE_LOG(TestProject2, Verbosity, TEXT("%s"),  *TLOG_CALLINFO)
#define TLOG(Verbosity, Format, ...) UE_LOG(TestProject2, Verbosity, TEXT("%s %s"), *TLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define TCHECK(Expr, ...) { if(!(Expr)) {TLOG(Error,TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }