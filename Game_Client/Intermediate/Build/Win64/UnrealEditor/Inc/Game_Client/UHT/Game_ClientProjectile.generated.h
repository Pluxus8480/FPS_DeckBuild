// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game_ClientProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef GAME_CLIENT_Game_ClientProjectile_generated_h
#error "Game_ClientProjectile.generated.h already included, missing '#pragma once' in Game_ClientProjectile.h"
#endif
#define GAME_CLIENT_Game_ClientProjectile_generated_h

#define FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnHit);


#define FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGame_ClientProjectile(); \
	friend struct Z_Construct_UClass_AGame_ClientProjectile_Statics; \
public: \
	DECLARE_CLASS(AGame_ClientProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Game_Client"), NO_API) \
	DECLARE_SERIALIZER(AGame_ClientProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AGame_ClientProjectile(AGame_ClientProjectile&&); \
	AGame_ClientProjectile(const AGame_ClientProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGame_ClientProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGame_ClientProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGame_ClientProjectile) \
	NO_API virtual ~AGame_ClientProjectile();


#define FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_12_PROLOG
#define FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAME_CLIENT_API UClass* StaticClass<class AGame_ClientProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Game_Client_Source_Game_Client_Game_ClientProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
