// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    PREINIT,
    LOADING,
    READY,
    DEAD
};

/** 디버깅용 로그 매크로 */
DECLARE_LOG_CATEGORY_EXTERN(LooterShooter, Log, All);
#define LSLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LSLOG_S(Verbosity) UE_LOG(LooterShooter, Verbosity, TEXT("%s"), *LSLOG_CALLINFO)
#define LSLOG(Verbosity, Format, ...) UE_LOG(LooterShooter, Verbosity, TEXT("%s %s"), *LSLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
// 매크로 안의 조건이 참이 아닌 경우 로그가 붉게 뜬다.
#define LSCHECK(Expr, ...) { if (!(Expr)) { LSLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}