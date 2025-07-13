// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game_ClientGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAME_CLIENT_Game_ClientGameMode_generated_h
#error "Game_ClientGameMode.generated.h already included, missing '#pragma once' in Game_ClientGameMode.h"
#endif
#define GAME_CLIENT_Game_ClientGameMode_generated_h

#define FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGame_ClientGameMode(); \
	friend struct Z_Construct_UClass_AGame_ClientGameMode_Statics; \
public: \
	DECLARE_CLASS(AGame_ClientGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Game_Client"), GAME_CLIENT_API) \
	DECLARE_SERIALIZER(AGame_ClientGameMode)


#define FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AGame_ClientGameMode(AGame_ClientGameMode&&); \
	AGame_ClientGameMode(const AGame_ClientGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAME_CLIENT_API, AGame_ClientGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGame_ClientGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGame_ClientGameMode) \
	GAME_CLIENT_API virtual ~AGame_ClientGameMode();


#define FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_9_PROLOG
#define FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAME_CLIENT_API UClass* StaticClass<class AGame_ClientGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
