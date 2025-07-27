// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LOG_SUBLOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetLocalRole()))
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
#define LOG_SUBREMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetRemoteRole()))
#define LOG_NETWORKINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("[CLIENT_%d]"), UE::GetPlayInEditorID())  : (GetNetMode() == ENetMode::NM_Standalone) ? *FString::Printf(TEXT("[STANDALONE]")) : *FString::Printf(TEXT("[SERVER]")) )
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)
#define HJ_LOG(LogCategory, Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("[%s] [%s/%s] %s %s"),LOG_NETWORKINFO, LOG_LOCALROLEINFO,LOG_REMOTEROLEINFO ,LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__) )

#define HJ_SUBLOG(LogCategory, Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("[%s] [%s/%s] %s %s"),LOG_NETWORKINFO, LOG_SUBLOCALROLEINFO,LOG_SUBREMOTEROLEINFO ,LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__) )

DECLARE_LOG_CATEGORY_EXTERN(LogHJNetwork, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHJMove, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHJDefault, Log, All);