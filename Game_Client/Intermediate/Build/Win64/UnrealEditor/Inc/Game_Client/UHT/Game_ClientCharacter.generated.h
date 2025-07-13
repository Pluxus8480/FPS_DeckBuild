// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game_ClientCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAME_CLIENT_Game_ClientCharacter_generated_h
#error "Game_ClientCharacter.generated.h already included, missing '#pragma once' in Game_ClientCharacter.h"
#endif
#define GAME_CLIENT_Game_ClientCharacter_generated_h

#define FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGame_ClientCharacter(); \
	friend struct Z_Construct_UClass_AGame_ClientCharacter_Statics; \
public: \
	DECLARE_CLASS(AGame_ClientCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Game_Client"), NO_API) \
	DECLARE_SERIALIZER(AGame_ClientCharacter)


#define FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AGame_ClientCharacter(AGame_ClientCharacter&&); \
	AGame_ClientCharacter(const AGame_ClientCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGame_ClientCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGame_ClientCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGame_ClientCharacter) \
	NO_API virtual ~AGame_ClientCharacter();


#define FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_19_PROLOG
#define FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_22_INCLASS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAME_CLIENT_API UClass* StaticClass<class AGame_ClientCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Game_Client_Source_Game_Client_Game_ClientCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
