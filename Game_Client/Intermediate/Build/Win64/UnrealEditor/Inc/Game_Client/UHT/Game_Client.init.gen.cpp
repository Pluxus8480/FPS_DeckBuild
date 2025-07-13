// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGame_Client_init() {}
	GAME_CLIENT_API UFunction* Z_Construct_UDelegateFunction_Game_Client_OnPickUp__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Game_Client;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Game_Client()
	{
		if (!Z_Registration_Info_UPackage__Script_Game_Client.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Game_Client_OnPickUp__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Game_Client",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xB22198A7,
				0xE986F742,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Game_Client.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Game_Client.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Game_Client(Z_Construct_UPackage__Script_Game_Client, TEXT("/Script/Game_Client"), Z_Registration_Info_UPackage__Script_Game_Client, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xB22198A7, 0xE986F742));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
