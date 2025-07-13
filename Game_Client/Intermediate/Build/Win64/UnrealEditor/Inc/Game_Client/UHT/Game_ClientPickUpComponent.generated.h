// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Game_ClientPickUpComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class AGame_ClientCharacter;
class UPrimitiveComponent;
struct FHitResult;
#ifdef GAME_CLIENT_Game_ClientPickUpComponent_generated_h
#error "Game_ClientPickUpComponent.generated.h already included, missing '#pragma once' in Game_ClientPickUpComponent.h"
#endif
#define GAME_CLIENT_Game_ClientPickUpComponent_generated_h

#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_12_DELEGATE \
GAME_CLIENT_API void FOnPickUp_DelegateWrapper(const FMulticastScriptDelegate& OnPickUp, AGame_ClientCharacter* PickUpCharacter);


#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnSphereBeginOverlap);


#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGame_ClientPickUpComponent(); \
	friend struct Z_Construct_UClass_UGame_ClientPickUpComponent_Statics; \
public: \
	DECLARE_CLASS(UGame_ClientPickUpComponent, USphereComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Game_Client"), NO_API) \
	DECLARE_SERIALIZER(UGame_ClientPickUpComponent)


#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGame_ClientPickUpComponent(UGame_ClientPickUpComponent&&); \
	UGame_ClientPickUpComponent(const UGame_ClientPickUpComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGame_ClientPickUpComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGame_ClientPickUpComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGame_ClientPickUpComponent) \
	NO_API virtual ~UGame_ClientPickUpComponent();


#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_14_PROLOG
#define FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAME_CLIENT_API UClass* StaticClass<class UGame_ClientPickUpComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Game_Client_Source_Game_Client_Game_ClientPickUpComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
