// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Game_Client/Game_ClientGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGame_ClientGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
GAME_CLIENT_API UClass* Z_Construct_UClass_AGame_ClientGameMode();
GAME_CLIENT_API UClass* Z_Construct_UClass_AGame_ClientGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Game_Client();
// End Cross Module References

// Begin Class AGame_ClientGameMode
void AGame_ClientGameMode::StaticRegisterNativesAGame_ClientGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGame_ClientGameMode);
UClass* Z_Construct_UClass_AGame_ClientGameMode_NoRegister()
{
	return AGame_ClientGameMode::StaticClass();
}
struct Z_Construct_UClass_AGame_ClientGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game_ClientGameMode.h" },
		{ "ModuleRelativePath", "Game_ClientGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGame_ClientGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AGame_ClientGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Game_Client,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGame_ClientGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGame_ClientGameMode_Statics::ClassParams = {
	&AGame_ClientGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGame_ClientGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AGame_ClientGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGame_ClientGameMode()
{
	if (!Z_Registration_Info_UClass_AGame_ClientGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGame_ClientGameMode.OuterSingleton, Z_Construct_UClass_AGame_ClientGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGame_ClientGameMode.OuterSingleton;
}
template<> GAME_CLIENT_API UClass* StaticClass<AGame_ClientGameMode>()
{
	return AGame_ClientGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGame_ClientGameMode);
AGame_ClientGameMode::~AGame_ClientGameMode() {}
// End Class AGame_ClientGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGame_ClientGameMode, AGame_ClientGameMode::StaticClass, TEXT("AGame_ClientGameMode"), &Z_Registration_Info_UClass_AGame_ClientGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGame_ClientGameMode), 2335630486U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_435535005(TEXT("/Script/Game_Client"),
	Z_CompiledInDeferFile_FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Game_Client_Source_Game_Client_Game_ClientGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
