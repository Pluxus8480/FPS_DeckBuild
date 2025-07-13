// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game_ClientWeaponComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AGame_ClientCharacter;
#ifdef GAME_CLIENT_Game_ClientWeaponComponent_generated_h
#error "Game_ClientWeaponComponent.generated.h already included, missing '#pragma once' in Game_ClientWeaponComponent.h"
#endif
#define GAME_CLIENT_Game_ClientWeaponComponent_generated_h

#define FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execEndPlay); \
	DECLARE_FUNCTION(execFire); \
	DECLARE_FUNCTION(execAttachWeapon);


#define FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGame_ClientWeaponComponent(); \
	friend struct Z_Construct_UClass_UGame_ClientWeaponComponent_Statics; \
public: \
	DECLARE_CLASS(UGame_ClientWeaponComponent, USkeletalMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Game_Client"), NO_API) \
	DECLARE_SERIALIZER(UGame_ClientWeaponComponent)


#define FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGame_ClientWeaponComponent(UGame_ClientWeaponComponent&&); \
	UGame_ClientWeaponComponent(const UGame_ClientWeaponComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGame_ClientWeaponComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGame_ClientWeaponComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGame_ClientWeaponComponent) \
	NO_API virtual ~UGame_ClientWeaponComponent();


#define FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_11_PROLOG
#define FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAME_CLIENT_API UClass* StaticClass<class UGame_ClientWeaponComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Game_Client_Source_Game_Client_Game_ClientWeaponComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
